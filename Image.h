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
    std::vector<std::vector<unsigned char>> data;

public:
    // Image(int w, int h) : width(w), height(h), data(h, std::vector<unsigned char>(w * static_cast<int>(C))) {}
    Image() : width(0), height(0) {}

    int getWidth() const override { return width; }

    int getHeight() const override { return height; }

    void setWidth(int w) override { width = w; }

    void setHeight(int h) override { height = h; }

    float getPixel(int x, int y, int c) const override {
        return data[y][x * static_cast<int>(C) + c];
    }

    void setPixel(int x, int y, int c, float value) override {
        data[y][x * static_cast<int>(C) + c] = value;
    };

    // const std::vector<std::vector<unsigned char>>& getData() const { return data; }

    int operator()(int x, int y) const override {
        return data[y][x * static_cast<int>(C)];
    }

    Channel getChannels() const override { return C; }

    void setData(const std::vector<std::vector<unsigned char>> &newData) override { data = newData; }


    /*ImageBase* clone() const override {
        Image<C> newImage;
        newImage.setWidth(width);
        newImage.setHeight(height);
        newImage.setData(data);
        return newImage;
    }*/

};

#endif //KERNELPROCESSING_IMAGE_H
