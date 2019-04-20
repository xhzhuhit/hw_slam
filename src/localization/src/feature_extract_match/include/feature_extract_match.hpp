#ifndef FEATURE_EXTRACT_MATCH_HPP
#define FEATURE_EXTRACT_MATCH_HPP
#include "common_header.h"

void find_feature_matches(cv::Mat& img1,
                        cv::Mat& img2,
                        std::vector<cv::KeyPoint>& keypoints_1,
                        std::vector<cv::KeyPoint>& keypoints_2,
                        std::vector<cv::DMatch>& matches);

#endif
