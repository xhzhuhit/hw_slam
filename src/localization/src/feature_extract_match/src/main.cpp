//#include <iostream>
//#include <vector>
//#include <opencv2/core/core.hpp>
//#include <opencv2/features2d/features2d.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include "../include/common_header.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Wrong Use !" << std::endl;
        std::cout << "Usage: ./main img1 img2" << std::endl;
        exit(0);
    }
    //cv::Point2d pt1(1.5, 67);
    //std::cout << pt1.x << "  " << pt1.y << std::endl;
    //read image
    cv::Mat img_10 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_20 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_1;
    cv::resize(img_10, img_1, cv::Size(800, 500), CV_INTER_CUBIC);
    cv::Mat img_2;
    cv::resize(img_20, img_2, cv::Size(800, 500), CV_INTER_CUBIC);
    //initialization
    std::vector<cv::KeyPoint> keypoints_1;
    std::vector<cv::KeyPoint> keypoints_2;
    cv::Mat descriptors_1;
    cv::Mat descriptors_2;
    cv::Ptr<cv::ORB> orb = cv::ORB::create(500, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
    //detect orb 角点
    orb->detect(img_1, keypoints_1);
    orb->detect(img_2, keypoints_2);
    //calculate brief 描述子
    orb->compute(img_1, keypoints_1, descriptors_1);
    orb->compute(img_2, keypoints_2, descriptors_2);
    
    cv::Mat outimg_1;
    cv::drawKeypoints(img_1, keypoints_1, outimg_1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    cv::imshow("ORB features",outimg_1);
    //do match, use Hamming 距离
    std::vector<cv::DMatch> matches;
    cv::BFMatcher matcher(cv::NORM_HAMMING);
    matcher.match(descriptors_1, descriptors_2, matches);
    //筛选匹配点
    double min_dist = 10000;
    double max_dist = 0;
    for (int i = 0; i < descriptors_1.rows; ++i) {
        double dist = matches[i].distance;
        if (dist < min_dist) {
            min_dist = dist;
        }
        if (dist > max_dist) {
            max_dist = dist;
        }
    }
    std::cout << "max dist: " << max_dist << std::endl;
    std::cout << "min dist: " << min_dist << std::endl;
    //当描述子之间的距离大于两倍的最小距离时，即认为匹配有误
    //但是有时候最小距离会非常小，设置一个经验值作为下线。
    std::vector<cv::DMatch> good_matches;
    for (int i = 1; i < descriptors_1.rows; ++i) {
        if (matches[i].distance < std::max(2 * min_dist, 30.0)) {
            //if (good_matches.size() < 500) {
                good_matches.push_back(matches[i]);
            //}
        }
    }
    //绘制匹配结果
    cv::Mat img_match;
    cv::Mat img_goodmatch;
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match); 
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
    cv::imshow("All matches", img_match);
    cv::imshow("Good matches", img_goodmatch); 
    cv::waitKey(0);
    return 1;
}
