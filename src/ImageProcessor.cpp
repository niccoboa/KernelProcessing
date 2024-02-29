#include "ImageProcessor.h"
#include "Channel.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <filesystem> // C++17


void ImageProcessor::load(ImageBase &image, const std::string &filepath) {
    //extract filename from path (C++17)
    std::string filename = std::filesystem::path(filepath).filename().string();

    auto start_time = std::chrono::steady_clock::now(); // loading start time
    try {
        std::ifstream inputFile(filepath, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Unable to open the file " + filepath);
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
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width * static_cast<int>(c); x++) {
                    //inputFile >> pixelData[y][x];
                    int pixelValue;
                    inputFile >> pixelValue;
                    pixelData[y][x] = static_cast<unsigned char>(pixelValue);
                }
            }
        } else if (magicNumber == "P5" || magicNumber == "P6") { // if P5 o P6, read data as byte
            for (int y = 0; y < height; y++) {
                for (int x = 0; x < width; x++) {
                    for (int ch = 0; ch < static_cast<int>(c); ch++) {
                        unsigned char byteValue;
                        inputFile.read(reinterpret_cast<char *>(&byteValue), 1); // read one byte
                        pixelData[y][x * static_cast<int>(c) + ch + 2] = byteValue; // careful with the channel offset
                    }
                }
            }
        } else {
            throw std::runtime_error("Error while reading the file");
        }

        image.setWidth(width);
        image.setHeight(height);
        image.setData(pixelData);
        image.setMaxValue(maxValue);
        inputFile.close();

        auto end_time = std::chrono::steady_clock::now(); // loading end time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time); // loading length
        std::cout << "1) File " << filename << " loaded in " << duration.count()
                  << " ms";
        std::cout << " (dimensions: " << width << "x" << height << ", channels used: " << static_cast<int>(c) << ")"
                  << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Error while loading the image: " << e.what() << std::endl;
        throw;
    }
}

void ImageProcessor::saveAs(ImageBase &image, const std::string &filename) {

    if (image.getChannels() == Channel::GRAY) {
        return saveImage(image, filename + ".pgm", "P2");
    } else if (image.getChannels() == Channel::RGB || image.getChannels() == Channel::RGBA) {
        return saveImage(image, filename + ".ppm", "P3");
    } else { //if (C == Channel::DUAL) {
        std::cerr << "Not supported channel type" << std::endl;
        throw;
    }
}

void ImageProcessor::saveImage(ImageBase &image, const std::string &filepath, const std::string &magic) {

    try {
        std::ofstream file(filepath);
        if (!file) {
            throw std::runtime_error("Unable to open the file " + filepath);
        }

        file << magic << std::endl;
        file << image.getWidth() << " " << image.getHeight() << std::endl;
        file << image.getMaxValue() << std::endl;


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
        throw;
    }

    std::cout << "3) Image saved in " << filepath << std::endl;
}

void ImageProcessor::applyKernel(ImageBase &image, const std::vector<std::vector<float>> &kernel) {

    // Check if the kernel is empty or bigger than the image
    if (kernel.empty() || kernel[0].empty()) {
        throw std::runtime_error("Kernel is empty");
    }

    int kw = static_cast<int>(kernel[0].size()); // kernel width
    int kh = static_cast<int>(kernel.size());    // kernel height
    int kwRadius = kw / 2; // kernel width radius
    int khRadius = kh / 2; // kernel height radius

    int w = image.getWidth(); // image width
    int h = image.getHeight(); // image height
    auto max = static_cast<float>(image.getMaxValue()); // max pixel value (float to avoid further casts)
    int c = static_cast<int>(image.getChannels()); // number of channels

    int max_threshold = 0; // counter for saturation (above 'max') values
    int min_threshold = 0; // counter for below zero values

    ImageBase *result = image.clone(); // clone the original image (be careful w/ memory leaks, delete it after use)

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
                            sum += static_cast<float>(image.getPixel(px, py, ch)) * kernel[ky][kx];
                        } else { // if the pixel is outside the image set the value to the nearest pixel
                            sum += static_cast<float>(image.getPixel(x, y, ch)) * kernel[ky][kx];
                        }
                    }
                }

                // EDGE HANDLING: if the sum is above max or below 0, set the value to max or 0
                if (sum > max) { // above max
                    result->setPixel(x, y, ch, max);
                    max_threshold++;
                }
                else if (sum <= 0) { // below 0
                    result->setPixel(x, y, ch, 0);
                    min_threshold++;
                }
                else { // ok
                    result->setPixel(x, y, ch, static_cast<unsigned char>(sum));
                }
            }
        }
    }

    auto end_time = std::chrono::steady_clock::now(); // kernel application end time
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time); // kernel application length

    image.setData(result->getData()); // apply the result to the original image

    delete result; // deallocate the cloned image to avoid memory leaks

    std::cout << "2) Kernel (" << kw << "x" << kh << ") applied in " << duration.count()
              << "ms" << std::endl;
    std::cout << "   Note: exceeded the saturation thresholds for " << max_threshold + min_threshold << " times (<0:" << max_threshold << " ; >" << max << ":" << min_threshold << ")" << std::endl;
}
