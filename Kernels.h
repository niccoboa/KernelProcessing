//
// Created by niccoboa on 20/02/2024.
//

#ifndef KERNELPROCESSING_KERNELS_H
#define KERNELPROCESSING_KERNELS_H

#include <vector>

const std::vector<std::vector<float>> blur3x3 = {
        {1.0f / 9, 1.0f / 9, 1.0f / 9},
        {1.0f / 9, 1.0f / 9, 1.0f / 9},
        {1.0f / 9, 1.0f / 9, 1.0f / 9}
};

const std::vector<std::vector<float>> blur5x5 = {
        {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
        {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
        {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
        {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
        {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25}
};

const std::vector<std::vector<float>> edgeDetect3x3 = {
        {1, 0, -1},
        {0,  0, 0},
        {-1, 0, 1}
};



#endif //KERNELPROCESSING_KERNELS_H
