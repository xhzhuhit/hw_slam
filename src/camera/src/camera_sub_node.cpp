#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <string>

cv::Mat image;
cv::Mat image_hsv;
cv::Mat lanemarks;
std::vector<cv::Mat> channels;
int num = 1;
void image_callback(const sensor_msgs::ImageConstPtr& msg) {
    image = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::BGR8)->image;
    std::cout << num++ << std::endl;
    //std::cout << "channels: " << image.channels() << std::endl;
    //do lanemarking detection
    cv::cvtColor(image, image_hsv, cv::COLOR_BGR2HSV, 3);
    cv::inRange(image_hsv, cv::Scalar(0, 0, 180), cv::Scalar(255, 25, 255), lanemarks);
    for (int i = 0; i < lanemarks.cols; ++i) {
        for (int j = 0; j < lanemarks.rows; ++j) {
            //std::cout << lanemarks.at<cv::Vec3b>(i,j) << std::endl; 
                      //<< image.at<int>[i][j][1] << "\t"
                      //<< image.at<int>[i][j][2] << std::endl; 
        }
    }  
    std::cout << "channels lane1: " << lanemarks.channels() << std::endl; 
    cv::cvtColor(lanemarks, lanemarks, cv::COLOR_GRAY2BGR); 
    std::cout << "channels lane2: " << lanemarks.channels() << std::endl;
    cv::imshow("zhuxiaohui", lanemarks);
    //cv::split(image, channels);
    //cv::imshow("zhuxiaohui", channels[1]);
    cv::waitKey(1);
}

int main(int argc, char* argv[]) {
    ros::init(argc, argv, "image_listener");
    ros::NodeHandle nh;
    cv::namedWindow("zhuxiaohui");
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe("camera/image", 100, image_callback);
    //do lanemarking detection
    //cv::cvtColor(image, image_hsv, cv::COLOR_BGR2GRAY, 3); 
    //cv::namedWindow("hsv");
    //cv::imshow("hsv", image_hsv);
    //cv::waitKey(1);
    ros::spin();
    cv::destroyWindow("zhuxiaohui");
    return 0;
}
