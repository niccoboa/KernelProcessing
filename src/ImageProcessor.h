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
    static void load(ImageBase& image, const std::string& filepath); // Load image from file

    static void saveAs(ImageBase& image, const std::string& outPath, const std::string& filename) ; // Save image with custom name
    static void saveImage(ImageBase& image, const std::string& filepath, const std::string& magic) ; // Save image with custom name and magic number

    static void applyKernel(ImageBase& image, const std::vector<std::vector<float>>& kernel); // Apply kernel to image
};


#endif //KERNELPROCESSING_IMAGEPROCESSOR_H