#include "Image.h"
#include "Kernel.h"

int main() {

    try {
        Image<int> image(3);
        image.load("media/input/lena.ppm");
        image.saveImage("media/output/lenacoloredcharint");

    } catch (const std::exception &e) {
        std::cerr << "An error occurred." << std::endl;
    }

    return 0;
}