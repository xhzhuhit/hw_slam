#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <unistd.h>

#include <thread>
#include <mutex>
#include "src/feature_extract_match/include/feature_extract_match.hpp"

cv::Mat image1;
cv::Mat image2;
int count = 0;
//initialization
std::vector<cv::KeyPoint> keypoints_1;
std::vector<cv::KeyPoint> keypoints_2;
std::vector<cv::DMatch> good_matches;
int num = 0;
std::mutex mtx;

void image_callback(const sensor_msgs::ImageConstPtr& msg) {
    if (image1.empty() && image2.empty()) {
        //mtx.lock();
        ++count;
        image2 = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image;
        //std::cout << "ss1: " << image1.empty() << std::endl;
        //std::cout << "ss2: " << image2.empty() << std::endl;
        std::cout << "t: " << count << std::endl;
        //mtx.unlock();
    } else {
        //mtx.lock();
        ++count;
        image1 = image2;
        image2 = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image;
        //mtx.unlock();
        //std::cout << "ss1: " << image1.empty() << std::endl;
        //std::cout << "ss2: " << image2.empty() << std::endl;
        //std::cout << "ttt: " << count << std::endl;
    }
    //std::cout << num++ << std::endl;
}

void do_find_matches() {
    while (1 && ros::ok()) {
    //for (int i = 0; i < 10; ++i) {
        mtx.lock();
        //std::cout << "count: " << count << std::endl;
        //std::cout << "sss1: " << image2.empty() << std::endl;
        //cv::waitKey(1000);
        //sleep(1);
        if (!image1.empty()) {
            find_feature_matches(image1, image2, keypoints_1, keypoints_2, good_matches);
            //std::cout << "ss2: " << image1.empty() << "  " << image2.empty() << std::endl;
        }
        //std::cout << "tt2: " << count << std::endl;
        //std::cout << "sss2: " << good_matches.size() << std::endl;
        mtx.unlock();
        //绘制匹配结果
        //cv::Mat img_match;
        //cv::Mat img_goodmatch;
        //drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_match);
        //drawMatches(image1, keypoints_1, image2, keypoints_2, good_matches, img_goodmatch);
        //cv::imshow("All matches", img_match);
        //cv::imshow("Good matches", img_goodmatch);
        //cv::waitKey(0);
    }
    std::cout << "do find matches" << std::endl;
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("camera/image", 100, image_callback);
    //std::cout << "do find matches" << std::endl;
    std::thread t(do_find_matches);
    ros::spin();
    t.join();
    return 0;
}
