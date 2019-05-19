#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <string>
#include <stdio.h>
#include "../../localization/src/feature_extract_match/include/common_header.h"
int num = 1;
int main(int argc, char *argv[]) {
    cv::Ptr<cv::ORB> orb = cv::ORB::create(500, 1.2f, 8, 31, 0, 2, cv::ORB::HARRIS_SCORE, 31, 20);
    std::vector<cv::KeyPoint> keypoints_1;
    //int num = 1;
    std::string video_path = "/home/zhuxiaohui/hw_slam/src/camera/data/video_first_1.h264";
    ros::init(argc, argv, "image_publisher");
    ros::NodeHandle nh;
    //cv::namedWindow("publisher");
    image_transport::ImageTransport it(nh);
    image_transport::Publisher pub = it.advertise("camera/image", 100); 
    cv::VideoCapture img_cap;// = cv::VideoCapture;
    cv::Mat img(1920, 1208, CV_8UC3);
    img_cap.open(video_path);
    if (!img_cap.isOpened()) {
        std::cout << "video open failure !" << std::endl;
        exit(0);
    }  
    sensor_msgs::ImagePtr msg;
    ros::Rate loop_rate(30);
    char index[7]; 
    std::cout << img_cap.get(CV_CAP_PROP_FPS) << std::endl; 
    while (ros::ok()) {// && num <= 400) {
    //while(1) {
        img_cap >> img;
        //std::cout << "channels: " << img.channels() << std::endl;
        if (!img.empty()) {
            snprintf(index, 7, "%06d", num);
            std::cout << num++ << "\tindex: " << index << std::endl;
            cv::putText(img, index, cv::Point(1300, 100), cv::FONT_HERSHEY_PLAIN, 5, cv::Scalar(0,0,255));
            //cv::imshow("publisher", img);
            //cv::waitKey(1);
            //orb->detect(img, keypoints_1);
            //std::cout << keypoints_1.size() << std::endl;
            std_msgs::Header head;
            head.stamp = ros::Time::now();
            msg = cv_bridge::CvImage(head, sensor_msgs::image_encodings::BGR8, img).toImageMsg();
            pub.publish(msg);
        }
        ros::spinOnce();
        loop_rate.sleep();
    }    
    //ros::spinOnce();
    //loop_rate.sleep();
    return 0;
}   
