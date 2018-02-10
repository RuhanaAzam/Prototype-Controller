#include "Controller.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>



using namespace cv;
using namespace std;
Controller::Controller(int worker, int groupSize) // constructor

{

	this->worker = worker;
//	this->seg = seg;
//	cu = new ComUnit;
	Mat x(10, 10, CV_8UC1);
	this->groupSize = groupSize;
//	this->groups = new Mat[this->groupSize]; 

	this->clips = clips;

} 

/*
void Controller::send_group(){
	printf("%s\n", "send_group done");
}
*/
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

/*
void Controller::print_queue(std::queue<int> seg){
	int a;
	for(int i = 0; i < seg.size(); i++) {
		a = seg.front();
		seg.pop();
		printf("%d\n", a);
		seg.push(a);
	}
}
*/

