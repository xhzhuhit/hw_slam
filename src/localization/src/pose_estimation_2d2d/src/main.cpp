#include "../include/pose_estimation_2d2d.hpp"
#include "../../feature_extract_match/include/feature_extract_match.hpp"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Wrong use !" << std::endl;
        std::cout << "Usage: ./main img1 img2" << std::endl;
        exit(0);
    }
    //read image
    cv::Mat img_10 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_20 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_1;
    cv::resize(img_10, img_1, cv::Size(800, 500), CV_INTER_CUBIC);
    cv::Mat img_2;
    cv::resize(img_20, img_2, cv::Size(800, 500), CV_INTER_CUBIC);
    std::vector<cv::KeyPoint> keypoints_1;
    std::vector<cv::KeyPoint> keypoints_2;
    std::vector<cv::DMatch> matches;
    //do match
    find_feature_matches(img_1, img_2, keypoints_1, keypoints_2, matches);
    //use match to solve pnp
    cv::Mat R;
    cv::Mat t;
    pose_estimation_2d2d(keypoints_1, keypoints_2, matches, R, t);
    return 0;
}
