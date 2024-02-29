#include "Kernel.h"

#include <vector>

// Identity
const std::vector<std::vector<float>> identity = {
            {0, 0, 0},
            {0, 1, 0},
            {0, 0, 0}
};


// Blur: 3x3, 5x5
const std::vector<std::vector<std::vector<float>>> blur = {
        {
                {1.0f / 9,  1.0f / 9,  1.0f / 9},
                {1.0f / 9,  1.0f / 9,  1.0f / 9},
                {1.0f / 9,  1.0f / 9,  1.0f / 9}
        },
        {
                {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
                {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
                {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
                {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25},
                {1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25, 1.0f / 25}
        }

};

// function to create a squared kernel for blur with a given size
std::vector<std::vector<float>> customSquaredBlur(unsigned short int size) {
    auto denominator = static_cast<float>(size * size);
    std::vector<std::vector<float>> kernel(size, std::vector<float>(size, 1.0f / (denominator)));
    return kernel;
}


// Edge detection: 3x3 soft, 3x3 strong
const std::vector<std::vector<std::vector<float>>> edgeDetect = {
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


// Sharpen 3x3 soft, 3x3 strong
const std::vector<std::vector<std::vector<float>>> sharpen = {
        {
                {0, -0.8, 0},
                {-0.8, 3.2, -0.8},
                {0, -0.8, 0}
        },
        {
                {0, -1,   0},
                {-1,   5,   -1},
                {0, -1,   0}
        }
};

// Sobel: 3x3 horizontal, 3x3 vertical
const std::vector<std::vector<std::vector<float>>> sobel = {
        {
                {-1, 0, 1},
                {-2, 0, 2},
                {-1, 0, 1}
        },
        {
                {-1, -2, -1},
                {0, 0, 0},
                {1, 2, 1}
        }
};