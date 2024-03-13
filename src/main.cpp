#include "Image.h"
#include "KernelCreator.h"
#include "BlurCreator.h"
#include "EdgeCreator.h"
#include "SharpenCreator.h"

using ImageType = int; // define image type (e.g. int, float, double) to use
int main() {

    try {
        Image<ImageType> image(3); // create image with c channels
        image.load("media/input/lena.ppm"); // load image

        SharpenCreator<ImageType> factory; // Concrete Creator
        std::unique_ptr<KernelProduct<ImageType>> kernel = factory.createKernel(5); // Concrete Product
        kernel->applyKernel(image); // apply kernel to image

        image.saveImage("media/output/lena-sharpen"); // save image

    } catch (const std::exception &e) {
        std::cerr << "An error occurred." << std::endl;
    }

    return 0;
}