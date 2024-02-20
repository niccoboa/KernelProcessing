//
// Created by niccoboa on 19/02/2024.
//

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
    std::vector<std::vector<int>> data;

public:
    Image(int w, int h) : width(w), height(h), data(h, std::vector<int>(w * static_cast<int>(C))) {}
    Image() : width(0), height(0) {}

    int getWidth() const override { return width; }
    int getHeight() const override { return height; }

    void setWidth(int w) override { width = w; }
    void setHeight(int h) override { height = h; }

    int getPixel(int x, int y, int c) const override {
        return data[y][x * static_cast<int>(C) + c];
    }

    void setPixel(int x, int y, int c, int value) override {
        data[y][x * static_cast<int>(C) + c] = value;
    };

    const std::vector<std::vector<int>>& getData() const { return data; }

    const int& operator()(int x, int y) const override {
        return data[y][x * static_cast<int>(C)];
    }

    virtual Channel getChannels() const override { return C; }

    void setData(const std::vector<std::vector<int>>& newData) override { data = newData; }
};

#endif //KERNELPROCESSING_IMAGE_H
