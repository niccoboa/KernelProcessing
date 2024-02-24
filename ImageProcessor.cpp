#include "ImageProcessor.h"
#include "Channel.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


bool ImageProcessor::load(ImageBase &image, const std::string &filename) {

    auto start_time = std::chrono::steady_clock::now(); // loading start time
    try {
        std::ifstream inputFile(filename, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Unable to open the file " + filename);
        }

        Channel c = image.getChannels();
        std::string magicNumber;
        int width, height, maxValue;
        inputFile >> magicNumber >> width >> height >> maxValue;
        if (magicNumber != "P2" && magicNumber != "P3" && magicNumber != "P5" && magicNumber != "P6") {
            throw std::runtime_error("File format not supported");
        }

        std::vector<std::vector<unsigned char>> pixelData(height,
                                                          std::vector<unsigned char>(width * static_cast<int>(c)));
        if (magicNumber == "P2" || magicNumber == "P3") { // if P2 o P3, read data as int
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width * static_cast<int>(c); ++x) {
                    //inputFile >> pixelData[y][x];
                    int pixelValue;
                    inputFile >> pixelValue;
                    pixelData[y][x] = static_cast<unsigned char>(pixelValue);
                }
            }
        } else if (magicNumber == "P5" || magicNumber == "P6") { // if P5 o P6, read data as byte
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    for (int ch = 1; ch <= static_cast<int>(c); ch++) {
                        unsigned char value;
                        inputFile.read(reinterpret_cast<char *>(&value), 1);
                        // int channelIndex = (ch + 2) % 3; // Inverts channels order: BGR <-> RGB
                        pixelData[y][x * static_cast<int>(c) + ch + 1] = value; // new version
                    }
                }
            }
        } else {
            throw std::runtime_error("Error while reading the file");
        }

        image.setWidth(width);
        image.setHeight(height);
        image.setData(pixelData);
        inputFile.close();

        auto end_time = std::chrono::steady_clock::now(); // Misura il tempo di fine
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time); // Calcola la durata
        std::cout << "1) File " << filename << " loaded in " << duration.count()
                  << " ms";
        std::cout << " (dimensions: " << width << "x" << height << ", channels used: " << static_cast<int>(c) << ")"
                  << std::endl;
        return true;

    } catch (const std::exception &e) {
        std::cerr << "Error while loading the image: " << e.what() << std::endl;
        return false;
    }
}

__attribute__((unused)) bool ImageProcessor::save(ImageBase &image) {
    return saveAs(image, "output");
}

bool ImageProcessor::saveAs(ImageBase &image, const std::string &filename) {
    if (image.getChannels() == Channel::GRAY) {
        return saveImage(image, "../" + filename + ".pgm", "P2");
    } else if (image.getChannels() == Channel::RGB || image.getChannels() == Channel::RGBA) {
        return saveImage(image, "../" + filename + ".ppm", "P3");
    } else { //if (C == Channel::DUAL) {
        std::cerr << "Not supported channel type" << std::endl;
        return false;
    }
}

bool ImageProcessor::saveImage(ImageBase &image, const std::string &filename, const std::string &magic) {

    try {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open the file " + filename);
        }

        file << magic << std::endl;
        file << image.getWidth() << " " << image.getHeight() << std::endl;
        file << "255" << std::endl;

        for (int y = 0; y < image.getHeight(); y++) {
            for (int x = 0; x < image.getWidth(); x++) {
                for (int ch = 0; ch < static_cast<int>(image.getChannels()); ch++) {
                    file << image.getPixel(x, y, ch) << " ";
                }
            }
            file << std::endl;
        }

        file.close();
    } catch (const std::exception &e) {
        std::cerr << "Error while saving the image: " << e.what() << std::endl;
        return false;
    }

    std::cout << "3) Image saved in " << filename << std::endl;
    return true;
}

void ImageProcessor::applyKernel(ImageBase &image, const std::vector<std::vector<float>> &kernel) {
    int kw = static_cast<int>(kernel[0].size()); // kernel width
    int kh = static_cast<int>(kernel.size());    // kernel height
    int kwRadius = kw / 2; // kernel width radius
    int khRadius = kh / 2; // kernel height radius

    int w = image.getWidth(); // image width
    int h = image.getHeight(); // image height
    int c = static_cast<int>(image.getChannels()); // number of channels
    int count = 0; // counter for saturation

    ImageBase &result = image; // clone image (TODO: beautify it)

    auto start_time = std::chrono::steady_clock::now(); // kernel application start time

    int px, py; // pixel coordinates

    for (int y = 0; y < h; y++) { // for each pixel
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) { // for each channel
                float sum = 0;
                for (int ky = 0; ky < kh; ky++) { // for each kernel element
                    for (int kx = 0; kx < kw; kx++) {
                        px = x + kx - kwRadius;
                        py = y + ky - khRadius;
                        if (px >= 0 && px < w && py >= 0 && py < h) { // if the pixel is inside the image
                            sum += image.getPixel(px, py, ch) * kernel[ky][kx];
                        }
                    }
                }
                if (sum > 255) count++;
                result.setPixel(x, y, ch, sum > 255 ? 255 : sum < 0 ? 0 : sum);
            }
        }
    }

    auto end_time = std::chrono::steady_clock::now(); // kernel application end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calcola la durata

    image = result; // apply the result to the original image


    std::cout << "2) Kernel (" << kw << "x" << kh << ") applied in " << duration.count()
              << "ms" << std::endl;
    std::cout << "   Note: exceeded the saturation threshold " << count << " times" << std::endl;
}
