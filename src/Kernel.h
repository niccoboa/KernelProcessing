// TODO: THIS WILL BE THE FACTORY CLASS FOR KERNELS. IT WILL BE USED TO CREATE KERNELS AND STORE THEM.
// At the moment (march 7th), it only contains the default kernels as matrices.


#ifndef KERNELPROCESSING_KERNEL_H
#define KERNELPROCESSING_KERNEL_H

#include <vector>

// 'Default' kernels (as matrices)
extern const std::vector<std::vector<float>> identity;
extern const std::vector<std::vector<std::vector<float>>> blur;
extern const std::vector<std::vector<std::vector<float>>> edgeDetect;
extern const std::vector<std::vector<std::vector<float>>> sharpen;
extern const std::vector<std::vector<std::vector<float>>> sobel;

// Custom kernels (created using functions)
std::vector<std::vector<float>> customSquaredBlur(unsigned short int size); // create a blur kernel with a given size


#endif //KERNELPROCESSING_KERNEL_H
