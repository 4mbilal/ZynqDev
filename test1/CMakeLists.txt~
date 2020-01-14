cmake_minimum_required(VERSION 2.8)
project(TestProject)
find_package(OpenCV REQUIRED)
add_executable(main GPIOClass.cpp VDMA.cpp main.cpp)
#add_executable(main VDMA.cpp)
target_link_libraries(main ${OpenCV_LIBS})

