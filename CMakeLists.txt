cmake_minimum_required(VERSION 3.10)
project(KernelProcessing)

set(CMAKE_CXX_STANDARD 17)

# file(COPY media/input DESTINATION ${CMAKE_BINARY_DIR}) # copy input images folder to build directory


add_executable(KernelProcessing src/main.cpp
        src/ImageBase.h
        src/Image.h
        src/Kernel.h
        src/Channel.h
        src/ImageProcessor.h
        src/ImageProcessor.cpp
        )

# file(GLOB PGM_FILES "${CMAKE_BINARY_DIR}/media/*.pgm") # get all .pgm files
# file(GLOB PPM_FILES "${CMAKE_BINARY_DIR}/media/*.ppm") # get all .ppm files

add_subdirectory(tests) # add tests directory
