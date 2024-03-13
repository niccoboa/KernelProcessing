//
// CONCRETE CREATOR
//

#ifndef KERNELPROCESSING_BLURCREATOR_H
#define KERNELPROCESSING_BLURCREATOR_H

#include "KernelCreator.h"

template<typename T>
class BlurCreator : public KernelCreator<T> {
public:
    std::unique_ptr<KernelProduct<T>> createKernel(int size) override {
        std::vector<std::vector<float>> kernel(size, std::vector<float>(size));

        // set every element equal to 1/(size*size)
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                kernel[y][x] = 1.0f / static_cast<float>((size * size));
            }
        }
        return std::make_unique<KernelProduct<T>>(kernel);
    }
};

#endif //KERNELPROCESSING_BLURCREATOR_H
