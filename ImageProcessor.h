#ifndef KERNELPROCESSING_IMAGEPROCESSOR_H
#define KERNELPROCESSING_IMAGEPROCESSOR_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Image.h"
#include "Channel.h"

//template<Channel C>
class ImageProcessor {

public:

    // Read/Write images and kernel application methods
    static bool load(ImageBase& image, const std::string& filename); // Load image from file

    __attribute__((unused)) static bool save(ImageBase& image); // Save image with default name
    static bool saveAs(ImageBase& image, const std::string& filename) ; // Save image with custom name
    static bool saveImage(ImageBase& image, const std::string& filename, const std::string& magic) ; // Save image with custom name and magic number

    static void applyKernel(ImageBase& image, const std::vector<std::vector<float>>& kernel); // Apply kernel to image
};


#endif //KERNELPROCESSING_IMAGEPROCESSOR_H