cmake_minimum_required(VERSION 3.10)
project(KernelProcessing)

set(CMAKE_CXX_STANDARD 17)

# file(COPY media/input DESTINATION ${CMAKE_BINARY_DIR}) # copy input images folder to build directory


add_executable(KernelProcessing src/main.cpp
        src/Image.h
        src/KernelProduct.h
        src/KernelCreator.h
)

# file(GLOB PGM_FILES "${CMAKE_BINARY_DIR}/media/*.pgm") # get all .pgm files
# file(GLOB PPM_FILES "${CMAKE_BINARY_DIR}/media/*.ppm") # get all .ppm files

add_subdirectory(tests) # add tests directory
