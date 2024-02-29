#ifndef KERNELPROCESSING_IMAGEBASE_H
#define KERNELPROCESSING_IMAGEBASE_H

#include <vector>
#include "Channel.h"

class ImageBase {
public:
    [[nodiscard]] virtual int getWidth() const = 0;
    [[nodiscard]] virtual int getHeight() const = 0;
    [[nodiscard]] virtual int getMaxValue() const = 0;
    virtual void setWidth(int w) = 0;
    virtual void setHeight(int h) = 0;
    virtual void setMaxValue(int max) = 0;
    [[nodiscard]] virtual int getPixel(int x, int y, int c) const = 0;
    virtual void setPixel(int x, int y, int c, float value) = 0;
    // virtual const std::vector<std::vector<unsigned char>> & getData() const = 0;
    virtual void setData(const std::vector<std::vector<unsigned char>>& newData) = 0;
    [[nodiscard]] virtual const std::vector<std::vector<unsigned char>>& getData() const = 0;

    virtual int operator()(int x, int y) const = 0;

    [[nodiscard]] virtual Channel getChannels() const = 0;
    virtual ~ImageBase() = default;

    [[nodiscard]] virtual ImageBase* clone() const = 0;

};


#endif //KERNELPROCESSING_IMAGEBASE_H
