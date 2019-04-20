#ifndef POSE_2D2D_HPP
#define POSE_2D2D_HPP

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/calib3d.hpp>
#include <vector>
#include <iostream>

void pose_estimation_2d2d(std::vector<cv::KeyPoint> keypoints_1, 
                            std::vector<cv::KeyPoint> keypoints_2, 
                            std::vector<cv::DMatch> matches, 
                            cv::Mat &R,
                            cv::Mat &t);

#endif
