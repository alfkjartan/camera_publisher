#include <iostream>
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/opencv.hpp"

int main(int argc, char** argv) {
 
  cv::VideoCapture cap;
  cv::Mat img;

  if(!cap.open(0)) {
    if (!cap.open(1)) {
      ROS_ERROR("Could not open video stream");
      return 1;
    }
  }

  ros::init(argc, argv, "publish_laptop_camera");

  ros::NodeHandle nh;
  image_transport::ImageTransport it(nh);
  image_transport::Publisher pub = it.advertise("camera/image", 1);
  ros::Rate loop_rate(20);
  while (ros::ok()) {
    cap >> img;
    sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", img).toImageMsg();
    pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
