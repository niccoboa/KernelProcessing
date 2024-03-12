//
// CREATOR
//

#ifndef KERNELPROCESSING_KERNELCREATOR_H
#define KERNELPROCESSING_KERNELCREATOR_H

#include "KernelProduct.h"
#include "Image.h"

#include <vector>
#include <memory>

template<typename T>
class KernelCreator {
public:
    KernelCreator() = default;
    virtual std::unique_ptr<KernelProduct<T>> createKernel(const std::string &type);
    virtual ~KernelCreator() = default;
};

template<typename T>
std::unique_ptr<KernelProduct<T>> KernelCreator<T>::createKernel(const std::string &type) {
    std::unique_ptr<KernelProduct<T>> result;

    if(type == "blur") {
        std::vector<std::vector<float>> blurMatrix = {{1.0f/9, 1.0f/9, 1.0f/9},
                                                      {1.0f/9, 1.0f/9, 1.0f/9},
                                                      {1.0f/9, 1.0f/9, 1.0f/9}};
        result = std::make_unique<KernelProduct<T>>(blurMatrix);
    }
    else if(type == "sharpen") {
        std::vector<std::vector<float>> sharpenMatrix = {{0,  -1, 0},
                                                         {-1, 5,  -1},
                                                         {0,  -1, 0}};
        result = std::make_unique<KernelProduct<T>>(sharpenMatrix);
    }
    else if(type == "edge") {
        std::vector<std::vector<float>> edgeMatrix = {{0, 1, 0},
                                                      {1, -4, 1},
                                                      {0, 1, 0}};
        result = std::make_unique<KernelProduct<T>>(edgeMatrix);
    }
    else {
        std::cerr << "Invalid kernel type" << std::endl;
    }

    return result;
}

#endif //KERNELPROCESSING_KERNELCREATOR_H
