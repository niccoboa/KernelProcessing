#ifndef KERNELPROCESSING_IMAGE_H
#define KERNELPROCESSING_IMAGE_H

#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <filesystem>

template<typename T>
class Image {
private:
    int height;
    int width;
    int maxValue; // max pixel value of the image (e.g. 255 for 8-bit images)
    int channels; // number of channels (e.g. 3 for RGB images)
    std::vector<std::vector<T>> data; // image data (pixel values matrix)

public:
    // Constructors
    explicit Image(int c) : height(0), width(0), maxValue(255), channels(c) {}
    Image(const Image<T> &other) {
        height = other.height;
        width = other.width;
        maxValue = other.maxValue;
        channels = other.channels;
        data = other.data;
    }

    // Getters
    [[nodiscard]] int getWidth() const { return width; }
    [[nodiscard]] int getHeight() const { return height; }
    [[nodiscard]] int getMaxValue() const { return maxValue; }
    [[nodiscard]] int getChannels() const { return channels; }
    [[nodiscard]] const std::vector<std::vector<T>>& getData() const { return data; }
    T getPixel(T x, T y, int c) { return data[y][x * getChannels() + c]; }

    // Setters
    void setWidth(int w) { width = w; }
    void setHeight(int h) { height = h; }
    void setMaxValue(int mv) { maxValue = mv; }
    void setChannels(int c) { channels = c; }
    void setData(const std::vector<std::vector<T>> &d) { data = d; }
    void setPixel(int x, int y, T value) { data[y][x] = value; }

    // Methods
    void load(const std::string &filepath);
    void saveImage(const std::string &filepath);

private:
    // Helper methods
    void printLoadingInfo(const std::string &filepath);

};

// Implementation
template <typename T>
void Image<T>::load(const std::string &filepath) {
    std::ifstream inputFile(filepath, std::ios::binary);
    if (!inputFile) {
        std::cerr << "Unable to open the file " + filepath << std::endl;
        throw;
    }

    std::string magicNumber;
    int w, h, max;
    inputFile >> magicNumber >> w >> h >> max;
    if (magicNumber != "P2" && magicNumber != "P3" && magicNumber != "P5" && magicNumber != "P6") {
        std::cerr << "File format not supported" << std::endl;
        throw;
    }

    setWidth(w);
    setHeight(h);
    setMaxValue(max);

    data.resize(getHeight(), std::vector<T>(getWidth() * getChannels()));

    if (magicNumber == "P2" || magicNumber == "P3") { // if P2 o P3, read data as int
        T value; // pixel value
        for (int y = 0; y < getHeight(); y++) {
            for (int x = 0; x < getWidth() * getChannels(); x++) { // channels, remember to change this
                inputFile >> value;
                setPixel(x, y, value);
            }
        }
    } else if (magicNumber == "P5" || magicNumber == "P6") { // if P5 o P6, read data as byte
        T byteValue;
        for (int y = 0; y < getHeight(); y++) {
            for (int x = 0; x < getWidth() * getChannels(); x++) {
                inputFile.read(reinterpret_cast<char *>(&byteValue), 1); // read one byte
                // data[y][x] = static_cast<T>(byteValue);
                setPixel(x, y, static_cast<T>(byteValue));
            }
        }
    } else {
        throw std::runtime_error("Error while reading the file");
    }

    inputFile.close();
    printLoadingInfo(filepath);
}

template <typename T>
void Image<T>::printLoadingInfo(const std::string &filepath) {
    std::string filename = std::filesystem::path(filepath).filename().string();
    std::cout << "1) Image " << filename << " loaded (dimensions: " << width << "x" << height << ", channels used: " << channels << ")"
              << std::endl;
}

template<typename T>
void Image<T>::saveImage(const std::string &filepath) {

    std::string filename; // filepath & extension
    std::string magicNumber;


    if (this->getChannels() == 1) {  // 'this' to avoid unreachable code compiler warning
        filename = std::string(filepath) + std::string(".pgm");
        magicNumber = "P2";
    } else if(this->getChannels() == 3 || this->getChannels() == 4) {
        std::string(filepath).append(".ppm");
        filename = std::string(filepath) + std::string(".ppm");
        magicNumber = "P3";
    } else {
        throw std::runtime_error("Unsupported channel type");
    }

    try {
        std::ofstream file(filename);
        if (!file) {
            throw std::runtime_error("Unable to open the file " + filename);
        }

        // Write the image header
        file << magicNumber << std::endl;
        file << getWidth() << " " << getHeight() << std::endl;
        file << getMaxValue() << std::endl;

        // Write the image data
        for (int yp = 0; yp < getHeight(); yp++) {
            for (int xp = 0; xp < getWidth(); xp++) {
                for (int ch = 1; ch <= getChannels(); ch++) {
                    file << static_cast<int>(getPixel(xp, yp, ch)) << " ";
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

#endif //KERNELPROCESSING_IMAGE_H

