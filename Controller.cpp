#include "Controller.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>


using namespace cv;
using namespace std;

//#include "opencv2/core/mat.hpp"
//#include "opencv2/core.hpp"'
#include <opencv2/opencv.hpp>
#include "cv_serial.cpp"


class Controller{
	private:
		ComUnit * cu; // communication unit
		int worker; // ???
		std::queue<cv::Mat*> seg; //video segmetent 30 frames each

	public:
		Controller(int worker, std::queue <cv::Mat*> seg); 
		void send_group();
		void read_video();
		void print_queue(std::queue<int> seg);
};

Controller::Controller(int worker, std::queue <cv::Mat*> seg) // constructor
{
	this->worker = worker;
	this->groupSize = groupSize;
	this->clips = clips;
	cu = new ComUnit;
} 

void Controller::send_group(){
	cv::Mat * frames = seg.front();
	seg.pop();

	matwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram", frames[0]);
	//for(int i = 0; i < sizeof(frames); i++) {
	//	matwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram", frames[i]);
	//}


}

void Controller::read_video(string filename){
   VideoCapture cap("1.mp4"); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return;

   
//    Mat[this->groupSize] group;
    Mat group[30];
   

    //namedWindow("edges",1);
    // double fps = vidcap.get(CAP_PROP_FPS);
    for(;;)
    {
	int groupNum = 0;
	//for(int i = 0; i < this->groupSize; i++){
        for(int i = 0; i < 30; i++){
	  int frameNum = 1;
	  int frameId = cap.get(frameNum++);
	  Mat frame;
          cap >> frame; // get a new frame from camera

	  group[i] = frame;

	}

	clips->push(group);



	groupNum++;
      }

}


void Controller::print_queue(std::queue<int> seg){
	int a;
	for(int i = 0; i < seg.size(); i++) {
		a = seg.front();
		seg.pop();
		printf("%d\n", a);
		seg.push(a);
	}
}

