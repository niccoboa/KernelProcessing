//
// Created by niccoboa on 20/02/2024.
//

#ifndef KERNELPROCESSING_IMAGEBASE_H
#define KERNELPROCESSING_IMAGEBASE_H

#include <vector>

class ImageBase {
public:
    virtual int getWidth() const = 0;
    virtual int getHeight() const = 0;
    virtual void setWidth(int w) = 0;
    virtual void setHeight(int h) = 0;
    virtual int getPixel(int x, int y, int c) const = 0;
    virtual void setPixel(int x, int y, int c, int value) = 0;
    // virtual const std::vector<std::vector<unsigned char>> & getData() const = 0;
    virtual void setData(const std::vector<std::vector<unsigned char>>& newData) = 0;
    virtual int operator()(int x, int y) const = 0;

    virtual Channel getChannels() const = 0;
    virtual ~ImageBase() = default;
};


#endif //KERNELPROCESSING_IMAGEBASE_H
