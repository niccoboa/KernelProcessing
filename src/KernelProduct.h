//
// PRODUCT
//

#ifndef KERNELPROCESSING_KERNELPRODUCT_H
#define KERNELPROCESSING_KERNELPRODUCT_H

#include "Image.h"
#include <vector>

template<typename T>
class KernelProduct {
private:
    std::vector<std::vector<float>> data;
public:
    KernelProduct() = default;
    explicit KernelProduct(const std::vector<std::vector<float>> &d) : data(d) {}
    void applyKernel(Image<T> &image);

    [[nodiscard]] const std::vector<std::vector<float>>& getData() const { return data; }
    [[nodiscard]] float getKernelPixel(int y, int x) const { return data[y][x]; }

    [[nodiscard]] const std::vector<std::vector<float>>& getKernel() const { return data; }
};

template<typename T>
void KernelProduct<T>::applyKernel(Image<T> &image) {

    int kernelSize = data.size();       // (squared) kernel matrix size (e.g. 3->3x3)
    int kernelRadius = kernelSize / 2;  // radius of the squared kernel matrix (e.g. 3->1)
    int imageWidth = image.getWidth();  // image width in pixels
    int imageHeight = image.getHeight(); // image height in pixels
    int channels = image.getChannels(); // number of channels (e.g. 3 for RGB images)

    Image<T> newImage(image); // clone the image using copy constructor

    // apply kernel to the image
    for (int y = 0; y < imageHeight; y++) {
        for (int x = 0; x < imageWidth; x++) {
            for (int c = 0; c < channels; c++) {
                float sum = 0;
                for (int ky = 0; ky < kernelSize; ky++) {
                    for (int kx = 0; kx < kernelSize; kx++) {
                        int px = x + kx - kernelRadius;
                        int py = y + ky - kernelRadius;

                        // if the pixel is within the image boundaries, apply the kernel
                        if (px >= 0 && px < imageWidth && py >= 0 && py < imageHeight) {
                            sum += image.getPixel(px, py, c) * getKernelPixel(ky, kx);
                        } else {  // else, set pixel to the nearest boundary pixel
                            sum += image.getPixel(x, y, c) * getKernelPixel(ky, kx);
                        }
                    }
                }

                // if the sum is above the max value, set pixel to max value
                if (sum > image.getMaxValue()) {
                    sum = image.getMaxValue();
                } else if (sum < 0) {
                    sum = 0;
                }
                newImage.setPixel(y, x * channels + c, sum);
            }
        }
    }
    image.setData(newImage.getData());

    // std::cout << "2) Kernel applied to the image" << std::endl;
}

#endif //KERNELPROCESSING_KERNELPRODUCT_H
