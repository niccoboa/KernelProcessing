//
// Created by niccoboa on 13/03/2024.
//

#ifndef KERNELPROCESSING_EDGECREATOR_H
#define KERNELPROCESSING_EDGECREATOR_H

#include "KernelCreator.h"

template<typename T>
class EdgeCreator : public KernelCreator<T> {
public:
    std::unique_ptr<KernelProduct<T>> createKernel(int size) override {
        std::vector<std::vector<float>> kernel(size, std::vector<float>(size));

        // set 'size^2-1' in the center of the kernel and '-1' in the other cells
        int center = size / 2;
        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (y == center && x == center) {
                    kernel[y][x] = static_cast<float>(size * size - 1);
                } else {
                    kernel[y][x] = -1;
                }
            }
        }

        return std::make_unique<KernelProduct<T>>(kernel);
    }

};

#endif //KERNELPROCESSING_EDGECREATOR_H
