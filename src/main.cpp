#include "Image.h"
#include "KernelCreator.h"
#include "BlurCreator.h"
#include "EdgeCreator.h"

using ImageType = int;
int main() {

    try {
        Image<ImageType> image(3);
        image.load("media/input/lena.ppm");

        BlurCreator<ImageType> factory;
        std::unique_ptr<KernelProduct<ImageType>> kernel = factory.createKernel(7);
        kernel->applyKernel(image);

        image.saveImage("media/output/lena-blur");

    } catch (const std::exception &e) {
        std::cerr << "An error occurred." << std::endl;
    }

    return 0;
}