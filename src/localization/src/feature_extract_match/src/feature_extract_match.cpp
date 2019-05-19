# include "../include/feature_extract_match.hpp"

void find_feature_matches(cv::Mat& img_1,
                        cv::Mat& img_2,
                        std::vector<cv::KeyPoint>& keypoints_1,
                        std::vector<cv::KeyPoint>& keypoints_2,
                        std::vector<cv::DMatch>& good_matches) {
    //std::cout << "start do fmat" << std::endl;
    cv::Mat descriptors_1;
    cv::Mat descriptors_2;
    cv::Ptr<cv::ORB> orb = cv::ORB::create(500, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
    //detect orb 角点
    orb->detect(img_2, keypoints_1);
    orb->detect(img_2, keypoints_2);
    //calculate brief 描述子
    orb->compute(img_2, keypoints_1, descriptors_1);
    orb->compute(img_2, keypoints_2, descriptors_2);
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
    //std::vector<cv::DMatch> good_matches;
    for (int i = 1; i < descriptors_1.rows; ++i) {
        if (matches[i].distance < std::max(2 * min_dist, 30.0)) {
            //if (good_matches.size() < 500) {
                good_matches.push_back(matches[i]);
            //}
        }
    }
}
