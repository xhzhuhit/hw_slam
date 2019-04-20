cmake_minimum_required(VERSION 2.8)
project(testOp)

#find required opencv 
find_package(OpenCV REQUIRED) 
# directory of opencv headers 
include_directories(${OpenCV_INCLUDE_DIRS}) 
# name of executable file and path of source file 
add_executable(main src/main.cpp)
# directory of opencv library 
link_directories(${OpenCV_LIBRARY_DIRS}) 
# opencv libraries 
target_link_libraries(main ${OpenCV_LIBS})

add_executable(feature_match src/main_use_fe.cpp
                src/feature_extract_match.cpp)
target_link_libraries(feature_match ${OpenCV_LIBS})
