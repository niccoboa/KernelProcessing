//
// CONCRETE CREATOR
//

#ifndef KERNELPROCESSING_SHARPENCREATOR_H
#define KERNELPROCESSING_SHARPENCREATOR_H

//
// CONCRETE CREATOR
//

#include "KernelCreator.h"

template<typename T>
class SharpenCreator : public KernelCreator<T> {
public:
    std::unique_ptr<KernelProduct<T>> createKernel(int size) override {
        std::vector<std::vector<float>> kernel(size, std::vector<float>(size));

        int kernelCenter = size / 2;
        std::cout << "Kernel center: " << kernelCenter << std::endl;
        // sharpen kernel: size/2 in center and -1 in the central vertical and horizontal lines
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (x == kernelCenter && y == kernelCenter) {
                    kernel[y][x] = static_cast<float>(size * 2 - 1);
                } else if (x == size / 2 || y == size / 2) {
                    kernel[y][x] = -1.0f;
                } else {
                    kernel[y][x] = 0.0f;
                }
            }
        }

        return std::make_unique<KernelProduct<T>>(kernel);
    }
};

#endif //KERNELPROCESSING_SHARPENCREATOR_H
