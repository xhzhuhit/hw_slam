#include "../include/pose_estimation_2d2d.hpp"

void pose_estimation_2d2d(std::vector<cv::KeyPoint> keypoints_1, 
                            std::vector<cv::KeyPoint> keypoints_2, 
                            std::vector<cv::DMatch> matches, 
                            cv::Mat &R,
                            cv::Mat &t) {
    cv::Mat K = (cv::Mat_<double>(3, 3) << 1918.64, 0, 948.617, 0, 1924.48, 628.628, 0, 0, 1);
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;
    for (int i = 0; i < (int)matches.size(); ++i) {
        points1.push_back(keypoints_1[matches[i].queryIdx].pt);
        points2.push_back(keypoints_2[matches[i].queryIdx].pt);
    }
    //calc fundalmental
    cv::Mat fundalmental_matrix;
    fundalmental_matrix = cv::findFundamentalMat(points1, points2, CV_FM_8POINT);
    std::cout << "fundalmental_matrix is " << std::endl << fundalmental_matrix << std::endl;
    //calc essential
    cv::Point2d principal_point(948.617, 628.628);
    int focal_length = 1918;
    cv::Mat essential_matrix;
    essential_matrix = cv::findEssentialMat(points1, points2, focal_length, principal_point, cv::RANSAC);
    std::cout << "essential_matrix is " << std::endl << essential_matrix << std::endl;
    //calc 单应矩阵
    cv::Mat homography_matrix;
    homography_matrix = cv::findHomography(points1, points2, cv::RANSAC, 3, cv::noArray(), 2000, 0.99);
    std::cout << "homography_matrix is " << std::endl << homography_matrix << std::endl;
    //从本质矩阵中恢复旋转和平移信息
    cv::recoverPose(essential_matrix, points1, points2, R, t, focal_length, principal_point);
    std::cout << "R is " << std::endl << R << std::endl;
    std::cout << "t is " << std::endl << t << std::endl;
}
