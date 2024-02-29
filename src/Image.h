#ifndef KERNELPROCESSING_IMAGE_H
#define KERNELPROCESSING_IMAGE_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Channel.h"
#include "ImageBase.h"

template<Channel C>
class Image : public ImageBase {
private:
    int height;
    int width;
    int maxValue; // max pixel value of the image (e.g. 255 for 8-bit images)
    std::vector<std::vector<unsigned char>> data; // image data (pixel values matrix)

public:
    // Image(int w, int h) : width(w), height(h), data(h, std::vector<unsigned char>(w * static_cast<int>(C))) {}
    Image() : width(0), height(0), maxValue(0) {}

    [[nodiscard]] int getWidth() const override { return width; }

    [[nodiscard]] int getHeight() const override { return height; }

    void setWidth(int w) override { width = w; }

    void setHeight(int h) override { height = h; }

    [[nodiscard]] int getMaxValue() const override { return maxValue; }

    void setMaxValue(int max) override { maxValue = max; }

    [[nodiscard]] float getPixel(int x, int y, int c) const override {
        return data[y][x * static_cast<int>(C) + c];
    }

    void setPixel(int x, int y, int c, float value) override {
        data[y][x * static_cast<int>(C) + c] = static_cast<unsigned char>(value);
    };

    // const std::vector<std::vector<unsigned char>>& getData() const { return data; }

    int operator()(int x, int y) const override {
        return data[y][x * static_cast<int>(C)];
    }

    [[nodiscard]] Channel getChannels() const override { return C; }

    void setData(const std::vector<std::vector<unsigned char>> &newData) override { data = newData; }

    [[nodiscard]] const std::vector<std::vector<unsigned char>>& getData() const override {
        return data;
    }

    [[nodiscard]] ImageBase* clone() const override {
        auto* newImage = new Image<C>();  // Image<C> *newImage = new Image<C>();
        newImage->setWidth(width);
        newImage->setHeight(height);
        newImage->setData(data);
        return newImage;
    }

};

#endif //KERNELPROCESSING_IMAGE_H
