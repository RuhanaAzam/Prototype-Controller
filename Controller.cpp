#include "Controller.hpp"
#include "matSerial.cpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>


using namespace cv;
using namespace std;
 
//#include "opencv2/core/mat.hpp"
//#include "opencv2/core.hpp"'
#include "opencv2/opencv.hpp"
#include "cv_serial.cpp"



Controller::Controller(int worker, queue<Mat*> *clips, int groupSize) // constructor
{
	this->worker = worker;
	this->groupSize = groupSize;
	this->clips = clips;
	cu = new ComUnit;
} 

void Controller::send_group(){
	while(!clips->empty()) { // empties the queue
		cv::Mat * frames = clips->front();
		clips->pop();
		
		vector<unsigned char> buf = matWrite(frames[0]);
		cu->sent(buf); // send to comUnit

		cv::Mat a = matRead(buf);
		std::vector<int> params;
	    params.push_back(cv::IMWRITE_JPEG_QUALITY);
	    cv::imwrite("/Users/ruhana/CAM2/Prototype-Controller/final.jpeg", a, params);
	}
	

}

void Controller::read_video(string filename){
    VideoCapture cap(filename); // open the default camera
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
		cout << a << "\n";
		seg.push(a);
	}
}

