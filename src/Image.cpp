#include "Image.h"
#include <chrono>
#include <filesystem>

template <typename T>
void load(const std::string &filepath) {
    try {
        auto start_time = std::chrono::steady_clock::now(); // loading start time

        loadFromFile(filepath);

        auto end_time = std::chrono::steady_clock::now(); // loading end time
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                end_time - start_time); // loading length

        printLoadingInfo(duration, filepath);
    } catch (const std::exception &e) {
        std::cerr << "Error while loading the image: " << e.what() << std::endl; // printError(e);
        throw;
    }
}

template<typename T>
void loadFromFile(const std::string &filepath) {
    std::ifstream inputFile(filepath, std::ios::binary);
    if (!inputFile) {
        throw std::runtime_error("Unable to open the file " + filepath);
    }

    std::string magicNumber;
    unsigned int w, h; // width and height of the image we are going to load

    inputFile >> magicNumber >> w >> h >> maxValue;
    if (magicNumber != "P2" && magicNumber != "P3" && magicNumber != "P5" && magicNumber != "P6") {
        throw std::runtime_error("File format not supported");
    }

    std::vector<std::vector<T>> pixelData(height, std::vector<T>(width * channels));

    if (magicNumber == "P2" || magicNumber == "P3") { // if P2 o P3, read data as int
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width * channels; x++) {
                int pixelValue;
                inputFile >> pixelValue;
                pixelData[y][x] = static_cast<T>(pixelValue);
            }
        }
    } else if (magicNumber == "P5" || magicNumber == "P6") { // if P5 o P6, read data as byte
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                for (int ch = 0; ch < channels; ch++) {
                    unsigned char byteValue;
                    inputFile.read(reinterpret_cast<char *>(&byteValue), 1); // read one byte
                    pixelData[y][x * channels + ch] = static_cast<T>(byteValue);
                }
            }
        }
    } else {
        throw std::runtime_error("Error while reading the file");
    }

    setWidth(w);
    setHeight(h);
    setData(pixelData);

    inputFile.close();
}

template<typename T>
void printLoadingInfo(std::chrono::milliseconds duration, const std::string &filepath) const {
    std::string filename = std::filesystem::path(filepath).filename().string();
    std::cout << "1) File " << filename << " loaded in " << duration.count() << " ms";
    std::cout << " (dimensions: " << width << "x" << height << ", channels used: " << channels << ")"
              << std::endl;
}


// save image to file
template<typename T>
void saveAs(const std::string &filepath) {
    if (getChannels() == 1) {
        return saveImage(filepath + ".pgm", "P2");
    } else if (getChannels() == 3 || getChannels() == 4) {
        return saveImage(filepath + ".ppm", "P3");
    } else { //if (C == Channel::DUAL) {
        std::cerr << "Not supported channel type" << std::endl;
        throw;
    }

}

template<typename T>
void saveImage(const std::string &filepath, const std::string &magicNumber) {
    try {
        std::ofstream file(filepath);
        if (!file) {
            throw std::runtime_error("Unable to open the file " + filepath);
        }

        auto w = getWidth();
        auto h = getHeight();
        auto c = getChannels();
        auto max = getMaxValue();

        file << magicNumber << std::endl;
        file << w << " " << h << std::endl;
        file << max << std::endl;


        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                for (int ch = 0; ch < c; ch++) {
                    file << getPixel(x, y, ch) << " ";
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