project(tests)
add_subdirectory(lib)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests_run ../src/ImageProcessor.cpp ImageProcessor.cpp
        ../src/Kernel.h Kernel.cpp
        ../src/Image.h Image.cpp
        ../src/ImageBase.h ImageBase.cpp)

target_link_libraries(tests_run gtest gtest_main)