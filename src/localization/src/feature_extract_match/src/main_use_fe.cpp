# include "../include/feature_extract_match.hpp"

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
    std::vector<cv::DMatch> good_matches;
    find_feature_matches(img_1, img_2, keypoints_1, keypoints_2, good_matches);
    //绘制匹配结果
    //cv::Mat img_match;
    cv::Mat img_goodmatch;
    //drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_ma    tch);
    drawMatches(img_1, keypoints_1, img_2, keypoints_2, good_matches, img_goodmatch);
    //cv::imshow("All matches", img_match);
    cv::imshow("Good matches", img_goodmatch);
    cv::waitKey(0);
    return 1;
}
