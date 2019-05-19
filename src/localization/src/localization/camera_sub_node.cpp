#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <unistd.h>

#include <atomic>
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
std::atomic<bool> _update(false);

void image_callback(const sensor_msgs::ImageConstPtr& msg) {
    std::lock_guard<std::mutex> guard(mtx);
    //mtx.lock();
    if (image1.empty() && image2.empty()) {
        //mtx.lock();
        ++count;
        image2 = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image;
        //image2 = image1;
        //std::cout << "ss1: " << image1.empty() << std::endl;
        //std::cout << "ss2: " << image2.empty() << std::endl;
        std::cout << "tt: " << count << std::endl;
        //mtx.unlock();
    } else {
        //mtx.lock();
        ++count;
        //std::cout << "ss1: " << image1.empty() << std::endl;
        image1 = image2;
        //std::cout << "ss2: " << image1.empty() << std::endl;
        image2 = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image;
        if (count > 2) {
            _update = true;
        }
        //mtx.unlock();
        //std::cout << "ss1: " << image1.empty() << std::endl;
        //std::cout << "ss2: " << image2.empty() << std::endl;
        //std::cout << "ttt: " << count << std::endl;
    }
    //mtx.unlock();
    //std::cout << num++ << std::endl;
}

void do_find_matches() {
    while (1 && ros::ok()) {
    //for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> guard(mtx);
        //mtx.lock();
        //std::cout << "count: " << count << std::endl;
        //std::cout << "sss1: " << image2.empty() << std::endl;
        //cv::waitKey(1000);
        //sleep(1);
        if (!image1.empty() && _update) {
            find_feature_matches(image1, image2, keypoints_1, keypoints_2, good_matches);
            _update = false;
            //std::cout << "ss2: " << image1.empty() << "  " << image2.empty() << std::endl;
        }
        //std::cout << "tt2: " << count << std::endl;
        //std::cout << "sss2: " << good_matches.size() << std::endl;
        //mtx.unlock();
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
