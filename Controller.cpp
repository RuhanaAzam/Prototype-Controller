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
			
		for(int i = 0; i < (groupSize); i++) {

			vector<unsigned char> buf = matWrite(frames[0]);
			cu->sent(buf); // send to comUnit

			// ADDED FOR VERIFICATION
			cv::Mat a = matRead(buf);
			std::vector<int> params;
		    params.push_back(cv::IMWRITE_JPEG_QUALITY);
		    cv::imwrite("/Users/ruhana/CAM2/Prototype-Controller/final.jpeg", a, params);
			}	
	}
}
void Controller::read_video(string filename){

  cout << filename << endl;

//    VideoCapture cap(filename); // open the default camera

    VideoCapture cap(0);
    if(!cap.isOpened()){  // check if we succeeded
         cout << "It's not opening the file" << endl;
	 return;
    }
//    Mat[this->groupSize] group;
    Mat group[this->groupSize];
   
   
   cout << "Before for loop" << endl;
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
	if(waitKey(5000) > 0)
		break;
      }

}


void Controller::print_queue(queue<Mat*> *clips){
	cout << "Check queue by printing queue" << endl;
	Mat *a;

	int num = 0;
	for(int i = 0; i < clips->size(); i++) {
		a = clips->front();
		clips->pop();
		cout << a << endl;
		//num++;
		//cout << num << endl;
	}
}

