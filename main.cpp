#include "Controller.cpp"
#include <cstdio>
#include <queue>
#include <opencv2/opencv.hpp>
//#include <cv.h>
#include <opencv2/imgproc/imgproc.hpp>


int main() {
	std::queue <std::vector<cv::Mat> > * clips;

	cv::Mat pic = cv::imread("/Users/ruhana/CAM2/Prototype-Controller/Version 2.jpg", CV_LOAD_IMAGE_COLOR);
	int groupSize = 5;
	std::vector<cv::Mat> frames;
	for(int i = 0 ; i < groupSize; i++) {
		frames.push_back(pic.clone());
	}

	std::queue <std::vector<cv::Mat> > queue;
	clips = &queue;
	clips->push(frames); // add array to queue 


	Controller * c = new Controller(4,clips, groupSize);
	//c->push_test();
	//c->send_group();
	c->start();
	//c->read_video("video.MOV");
	//c->send_group();

	return 1;
}
//g++ $(pkg-config --cflags --libs opencv) -g main.cpp -o main
