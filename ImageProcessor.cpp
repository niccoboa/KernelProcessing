#include "ImageProcessor.h"
#include "Channel.h"
#include "Image.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>


bool ImageProcessor::load(ImageBase &image, const std::string &filename) {

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

        std::vector<std::vector<unsigned char>> pixelData(height,
                                                          std::vector<unsigned char>(width * static_cast<int>(c)));
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
                for (int x = 0; x < width; ++x) {
                    for (int ch = 0; ch < static_cast<int>(c); ++ch) {
                        unsigned char value;
                        inputFile.read(reinterpret_cast<char *>(&value), 1);
                        int channelIndex = (ch + 2) % 3; // Inverte l'ordine dei canali: BGR <-> RGB
                        pixelData[y][x * static_cast<int>(c) + channelIndex] = value;
                    }
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
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time); // Calcola la durata
        std::cout << "1) File " << filename << " aperto e letto correttamente in " << duration.count()
                  << " millisecondi";
        std::cout << " (dimensioni: " << width << "x" << height << ", numero canali: " << static_cast<int>(c) << ")"
                  << std::endl;
        return true;

    } catch (const std::exception &e) {
        std::cerr << "Errore durante il caricamento dell'immagine: " << e.what() << std::endl;
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
        std::cerr << "Canale non supportato" << std::endl;
        return false;
    }
}

bool ImageProcessor::saveImage(ImageBase &image, const std::string &filename, const std::string &magic) {

    try {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Impossibile aprire il file " + filename);
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
        std::cerr << "Errore durante il salvataggio dell'immagine: " << e.what() << std::endl;
        return false;
    }

    std::cout << "3) Immagine salvata correttamente in " << filename << std::endl;
    return true;
}

#include <iostream>
#include <chrono> // per misurare il tempo di esecuzione

void ImageProcessor::applyKernel(ImageBase &image, const std::vector<std::vector<float>> &kernel) {
    int kw = static_cast<int>(kernel[0].size()); // kernel width
    int kh = static_cast<int>(kernel.size());    // kernel height

    int w = image.getWidth();
    int h = image.getHeight();
    int c = static_cast<int>(image.getChannels());
    int count = 0;

    ImageBase &result = image; // Clona l'immagine originale per mantenere l'originale invariato

    auto start_time = std::chrono::steady_clock::now(); // Misura il tempo di inizio

    for (int y = 0; y < h; y++) { // per ogni pixel
        for (int x = 0; x < w; x++) {
            for (int ch = 1; ch <= c; ch++) { // per ogni canale
                float sum = 0;
                for (int ky = 0; ky < kh; ky++) { // per ogni elemento del kernel
                    for (int kx = 0; kx < kw; kx++) {
                        int px = x + kx - kw / 2;
                        int py = y + ky - kh / 2;
                        if (px >= 0 && px < w && py >= 0 &&
                            py < h) { // se il pixel è dentro l'immagine (non gestisco il padding)
                            sum += image.getPixel(px, py, ch) * kernel[ky][kx];
                        }
                    }
                }
                if (sum > 255) count++;
                result.setPixel(x, y, ch, sum > 255 ? 255 : sum < 0 ? 0 : sum);
            }
        }
    }

    auto end_time = std::chrono::steady_clock::now(); // Misura il tempo di fine
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time); // Calcola la durata

    image = result; // sostituisce l'immagine originale con il risultato


    std::cout << "2) Kernel (" << kw << "x" << kh << ") applicato correttamente in " << duration.count()
              << " millisecondi" << std::endl;
    std::cout << "   Nota: superata la soglia di saturazione per: " << count << " volte" << std::endl;
}

