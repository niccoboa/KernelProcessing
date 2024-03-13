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
    virtual std::unique_ptr<KernelProduct<T>> createKernel(int size) = 0;
    virtual ~KernelCreator() = default;
};


#endif //KERNELPROCESSING_KERNELCREATOR_H
