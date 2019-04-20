cmake_minimum_required(VERSION 2.8)
project(test_pose_2d2d)

add_definitions(-std=c++11)
SET(ROOT_DIR ~/hw_slam/src/localization)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(main src/main.cpp
                ${ROOT_DIR}/src/feature_extract_match/src/feature_extract_match.cpp
                src/pose_estimation_2d2d.cpp)
link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(main ${OpenCV_LIBS})
