#ifndef KERNELPROCESSING_KERNELS_H
#define KERNELPROCESSING_KERNELS_H

#include <vector>

const std::vector<std::vector<std::vector<float>>> blur = {
    {
            {1.0f/9, 1.0f/9, 1.0f/9},
            {1.0f/9, 1.0f/9, 1.0f/9},
            {1.0f/9, 1.0f/9, 1.0f/9}
    },
    {
            {1.0f/25, 1.0f/25, 1.0f/25,1.0f/25, 1.0f/25},
            {1.0f/25, 1.0f/25, 1.0f/25,1.0f/25, 1.0f/25},
            {1.0f/25, 1.0f/25, 1.0f/25,1.0f/25, 1.0f/25},
            {1.0f/25, 1.0f/25, 1.0f/25,1.0f/25, 1.0f/25},
            {1.0f/25, 1.0f/25, 1.0f/25,1.0f/25, 1.0f/25}
    }
};

const std::vector<std::vector<std::vector<float>>> edgeDetect3x3 = {
        {
                {0.75, 0, -0.75},
                {0, 0,  0},
                {-0.75, 0, 0.75}
        },
        {
                {-0.75, 0, 0.75},
                {0, 0,  0},
                {0.75, 0, -0.75}
        },
        {
                {0, 1, 0},
                {1, -4, 1},
                {0, 1, 0}
        },
        {
                {1, 1, 1},
                {1, -8, 1},
                {1, 1, 1}
        }
};

const std::vector<std::vector<std::vector<float>>> sharpen = {
        {
                {0, -0.8, 0},
                {-0.8, 3.2, -0.8},
                {0, -0.8, 0}
        },
        {
                {0, -1, 0},
                {-1, 5, -1},
                {0, -1, 0}
        }
};


#endif //KERNELPROCESSING_KERNELS_H
