//
// Created by niccoboa on 19/02/2024.
//

#include "ImageProcessor.h"
#include "Channel.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>


bool ImageProcessor::load(ImageBase& image, const std::string &filename) {
    try {
        std::ifstream inputFile(filename);
        if (!inputFile) {
            throw std::runtime_error("Impossibile aprire il file " + filename);
        }

        Channel c = image.getChannels();

        std::cout << "File " << filename << " aperto correttamente" << std::endl;
        std::string magicNumber;
        int width, height, maxValue;
        inputFile >> magicNumber >> width >> height >> maxValue;
        if (magicNumber != "P2" && magicNumber != "P3") {
            throw std::runtime_error("Il file non è in formato PGM o PPM ASCII");
        }

        std::vector<std::vector<int>> pixelData(height, std::vector<int>(width * static_cast<int>(c)));
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width * static_cast<int>(c); ++x) {
                inputFile >> pixelData[y][x];
            }
        }

        inputFile.close();

        image.setWidth(width);
        image.setHeight(height);
        image.setData(pixelData);

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Errore durante il caricamento dell'immagine: " << e.what() << std::endl;
        return false;
    }
}

bool ImageProcessor::save(ImageBase& image) {
    return saveAs(image, "output");
}

bool ImageProcessor::saveAs(ImageBase& image, const std::string &filename) {
    if (image.getChannels() == Channel::GRAY) {
        return saveImage(image, filename + ".pgm", "P2");
    } else if (image.getChannels() == Channel::RGB || image.getChannels() == Channel::RGBA) {
        return saveImage(image, filename + ".ppm", "P3");
    } else { //if (C == Channel::DUAL) {
        std::cerr << "Tipo di canale non (ancora?) supportato" << std::endl;
        return false;
    }
}

bool ImageProcessor::saveImage(ImageBase &image, const std::string &filename, const std::string &magic) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Errore nell'apertura del file " << filename << std::endl;
        return false;
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

    std::cout << "Immagine salvata correttamente in " << filename << std::endl;
    return true;
}

void ImageProcessor::applyKernel(ImageBase& image, const std::vector<std::vector<float>> &kernel) {
    int kw = static_cast<int>(kernel[0].size()); // kernel width
    int kh = static_cast<int>(kernel.size()); // kernel height
    int w = image.getWidth();
    int h = image.getHeight();
    int c = static_cast<int>(image.getChannels());

    ImageBase& result = image;

    for (int y = 0; y < h; y++) { // for each pixel
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) { // for each channel
                float sum = 0;
                for (int ky = 0; ky < kh; ky++) { // for each kernel element
                    for (int kx = 0; kx < kw; kx++) {
                        int px = x + kx - kw / 2;
                        int py = y + ky - kh / 2;
                        if (px >= 0 && px < w && py >= 0 && py < h) { // if the pixel is inside the image
                            sum += static_cast<float>(image.getPixel(px, py, ch)) * kernel[ky][kx];
                        }
                    }
                }
                result.setPixel(x, y, ch, static_cast<int>(sum));
            }
        }
    }

    image = result; // replace the original image with the result
    std::cout << "Kernel applicato correttamente" << std::endl;
}
