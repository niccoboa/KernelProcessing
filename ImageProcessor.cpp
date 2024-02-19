//
// Created by niccoboa on 19/02/2024.
//

#include "ImageProcessor.h"
#include "Channel.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>


template<Channel C> bool ImageProcessor<C>::load(const std::string &filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Impossibile aprire il file " << filename << std::endl;
        return false;
    }
    std::cout << "File " << filename << " aperto correttamente" << std::endl;
    std::string magicNumber;
    int width, height, maxValue;
    inputFile >> magicNumber >> width >> height >> maxValue;
    if (magicNumber != "P2" && magicNumber != "P3") {
        std::cerr << "Il file non è in formato PGM o PPM" << std::endl;
        return false;
    }
    std::vector<std::vector<int>> pixelData(height, std::vector<int>(width * static_cast<int>(C)));
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width * static_cast<int>(C); ++x) {
            inputFile >> pixelData[y][x];
        }
    }

    inputFile.close();

    // Impostare i dati dell'immagine
    image = Image<C>(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            for (int ch = 0; ch < static_cast<int>(C); ++ch) {
                image.setPixel(x, y, ch, pixelData[y][x * static_cast<int>(C) + ch]);
            }
        }
    }

    return true;

}

template<Channel C> bool ImageProcessor<C>::save() const {
    return saveAs("output");
}

template<Channel C> bool ImageProcessor<C>::saveAs(const std::string &filename) const {
    if (C == Channel::GRAY) {
        return savePGM(filename + ".pgm");
    } else if (C == Channel::RGB || C == Channel::RGBA) {
        return savePPM(filename + ".ppm");
    } else { //if (C == Channel::DUAL) {
        std::cerr << "Tipo di canale non (ancora?) supportato" << std::endl;
        return false;
    }
}

template<Channel C> bool ImageProcessor<C>::savePGM(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Errore nell'apertura del file " << filename << std::endl;
        return false;
    }

    file << "P2" << std::endl;
    file << image.getWidth() << " " << image.getHeight() << std::endl;
    file << "255" << std::endl;

    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            file << image(x, y) << " ";
        }
        file << std::endl;
    }

    return true;
}

template<Channel C> bool ImageProcessor<C>::savePPM(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Errore nell'apertura del file " << filename << std::endl;
        return false;
    }

    file << "P3" << std::endl;
    file << image.getWidth() << " " << image.getHeight() << std::endl;
    file << "255" << std::endl;

    for (int y = 0; y < image.getHeight(); y++) {
        for (int x = 0; x < image.getWidth(); x++) {
            for (int ch = 0; ch < static_cast<int>(C); ch++) {
                file << image.getPixel(x, y, ch) << " ";
            }
        }
        file << std::endl;
    }

    return true;
}

template<Channel C> void ImageProcessor<C>::applyKernel(const std::vector<std::vector<float>> &kernel) {
    int kw = kernel[0].size(); // kernel width
    int kh = kernel.size(); // kernel height
    int w = image.getWidth();
    int h = image.getHeight();
    int c = static_cast<int>(C); // number of channels of the image

    Image<C> result(w, h); // create a new image to store the result

    for (int y = 0; y < h; y++) { // for each pixel
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) { // for each channel
                float sum = 0;
                for (int ky = 0; ky < kh; ky++) { // for each kernel element
                    for (int kx = 0; kx < kw; kx++) {
                        int px = x + kx - kw / 2;
                        int py = y + ky - kh / 2;
                        if (px >= 0 && px < w && py >= 0 && py < h) { // if the pixel is inside the image
                            sum += image.getPixel(px, py, ch) * kernel[ky][kx];
                        }
                    }
                }
                result.setPixel(x, y, ch, sum);
            }
        }
    }

    image = result; // replace the original image with the result
}