//
// Created by niccoboa on 19/02/2024.
//

#include "ImageProcessor.h"
#include "Channel.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


bool ImageProcessor::load(ImageBase& image, const std::string &filename) {
    auto start_time = std::chrono::steady_clock::now(); // Misura il tempo di inizio

    try {
        std::ifstream inputFile(filename, std::ios::binary);
        if (!inputFile) {
            throw std::runtime_error("Impossibile aprire il file " + filename);
        }

        Channel c = image.getChannels();
        std::string magicNumber;
        int width, height, maxValue;
        inputFile >> magicNumber >> width >> height >> maxValue;
        if (magicNumber != "P2" && magicNumber != "P3" && magicNumber != "P5" && magicNumber != "P6") {
            throw std::runtime_error("Il file non è in formato PGM o PPM");
        }

        std::vector<std::vector<unsigned char>> pixelData(height, std::vector<unsigned char>(width * static_cast<int>(c)));
        if (magicNumber == "P2" || magicNumber == "P3") { // se è P2 o P3, leggo i dati come interi
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width * static_cast<int>(c); ++x) {
                    //inputFile >> pixelData[y][x];
                    int pixelValue;
                    inputFile >> pixelValue;
                    pixelData[y][x] = static_cast<unsigned char>(pixelValue);
                }
            }
        } else if (magicNumber == "P5" || magicNumber == "P6") { // se è P5 o P6, leggo i dati come byte
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width * static_cast<int>(c); ++x) {
                    unsigned char value;
                    inputFile.read(reinterpret_cast<char*>(&value), 1);
                    pixelData[y][x] = value;
                }
            }
        } else {
            throw std::runtime_error("Errore durante la lettura del file");
        }

        image.setWidth(width);
        image.setHeight(height);
        image.setData(pixelData);
        inputFile.close();

        auto end_time = std::chrono::steady_clock::now(); // Misura il tempo di fine
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calcola la durata
        std::cout << "File " << filename << " aperto e letto correttamente in " << duration.count() << " millisecondi" << std::endl;
        return true;

    } catch (const std::exception& e) {
        std::cerr << "Errore durante il caricamento dell'immagine: " << e.what() << std::endl;
        return false;
    }
}

__attribute__((unused)) bool ImageProcessor::save(ImageBase& image) {
    return saveAs(image, "output");
}

bool ImageProcessor::saveAs(ImageBase& image, const std::string &filename) {
    if (image.getChannels() == Channel::GRAY) {
        return saveImage(image, "../" + filename + ".pgm", "P2");
    } else if (image.getChannels() == Channel::RGB || image.getChannels() == Channel::RGBA) {
        return saveImage(image, "../" + filename + ".ppm", "P3");
    } else { //if (C == Channel::DUAL) {
        std::cerr << "Canale non supportato" << std::endl;
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

#include <iostream>
#include <chrono> // per misurare il tempo di esecuzione

void ImageProcessor::applyKernel(ImageBase& image, const std::vector<std::vector<float>>& kernel) {
    int kw = static_cast<int>(kernel[0].size()); // kernel width
    int kh = static_cast<int>(kernel.size());    // kernel height
    int w = image.getWidth();
    int h = image.getHeight();
    int c = static_cast<int>(image.getChannels());

    ImageBase& result = image; // Clona l'immagine originale per mantenere l'originale invariato

    auto start_time = std::chrono::steady_clock::now(); // Misura il tempo di inizio

    int maxPixelValue = 0;
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) {
                int pixelValue = image.getPixel(x, y, ch);
                if (pixelValue > maxPixelValue) {
                    maxPixelValue = pixelValue;
                }
            }
        }
    }
    std::cout << "Max pixel value: " << maxPixelValue << std::endl;

    for (int y = 0; y < h; y++) { // per ogni pixel
        for (int x = 0; x < w; x++) {
            for (int ch = 0; ch < c; ch++) { // per ogni canale
                int sum = 0;
                for (int ky = 0; ky < kh; ky++) { // per ogni elemento del kernel
                    for (int kx = 0; kx < kw; kx++) {
                        int px = x + kx - kw / 2;
                        int py = y + ky - kh / 2;
                        if (px >= 0 && px < w && py >= 0 && py < h) { // se il pixel è dentro l'immagine (non gestisco il padding)
                            sum += image.getPixel(px, py, ch) * kernel[ky][kx];
                        }
                    }
                }
                // Applica la saturazione al valore del pixel risultante
                result.setPixel(x, y, ch, sum > 255 ? 255 : sum < 0 ? 0 : sum);
                //float normalizedValue = (sum / static_cast<float>(maxPixelValue)) * 255.0f;
                //result.setPixel(x, y, ch, static_cast<int>(normalizedValue));
            }
        }
    }

    auto end_time = std::chrono::steady_clock::now(); // Misura il tempo di fine
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calcola la durata

    image = result; // sostituisce l'immagine originale con il risultato

    std::cout << "Kernel applicato correttamente in " << duration.count() << " millisecondi" << std::endl;
}

