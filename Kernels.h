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

// sharpen kernel
const std::vector<std::vector<float>> sharpen3x3 = {
        {0, -1, 0},
        {-1, 5, -1},
        {0, -1, 0}
};

// evidenziazione dei bordi
const std::vector<std::vector<float>> edgeEnhance3x3 = {
        {0, -1, 0},
        {-1, 4, -1},
        {0, -1, 0}
};

// individuazione dei bordi 3x3 con -4 in mezzo
const std::vector<std::vector<float>> edgeDetect3x3_2 = {
        {0, 1, 0},
        {1, -4, 1},
        {0, 1, 0}
};


#endif //KERNELPROCESSING_KERNELS_H
