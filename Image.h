//
// Created by niccoboa on 19/02/2024.
//

#ifndef KERNELPROCESSING_IMAGE_H
#define KERNELPROCESSING_IMAGE_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Channel.h"


template<Channel C>
class Image {
private:
    int height;
    int width;
    std::vector<std::vector<int>> data;

public:
    Image(int w, int h);
    Image() : width(0), height(0) {}

    int getWidth() const;
    int getHeight() const;

    int getPixel(int x, int y, int c) const;
    void setPixel(int x, int y, int c, int value);

    // getData
    std::vector<std::vector<int>>& getData();

    // Operatore per accedere ai pixel (versione const)
    const int& operator()(int x, int y) const;
};


template<Channel C> Image<C>::Image(int w, int h) : width(w), height(h), data(h, std::vector<int>(w * static_cast<int>(C))) {}

//template<Channel C>
//Image<C>::Image() : Image(0, 0) {}

template<Channel C> int Image<C>::getWidth() const {
    return width;
}

template<Channel C> int Image<C>::getHeight() const {
    return height;
}

template<Channel C> int Image<C>::getPixel(int x, int y, int c) const {
    return data[y][x * static_cast<int>(C) + c];
}

template<Channel C> void Image<C>::setPixel(int x, int y, int c, int value) {
    data[y][x * static_cast<int>(C) + c] = value;
}

template<Channel C> std::vector<std::vector<int>>& Image<C>::getData() {
    return data;
}

template<Channel C> const int& Image<C>::operator()(int x, int y) const {
    //return data[y][x];
    return data[y][x * static_cast<int>(C)];
}

#endif //KERNELPROCESSING_IMAGE_H
