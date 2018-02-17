#include "Controller.hpp"
#include "matSerial.cpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>
#include <pthread.h>

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
	while(1) { 
			pthread_mutex_lock(&lock); // LOCK START ************************
			if(clips->empty()) { // exits function when empty
				pthread_mutex_unlock(&lock);
				return;
			} else {
				printf("#%lu REMOVED\n", clips->size());
				cv::Mat * frames = clips->front();
				clips->pop();
				pthread_mutex_unlock(&lock); // LOCK END ************************
				
				for(int i = 0; i < (groupSize); i++) { // sending 30 frames one by one
					vector<unsigned char> buf = matWrite(frames[i]);
					cu->sent(buf); // send to comUnit

					// ADDED FOR VERIFICATION // REMOVE LATER
					cv::Mat a = matRead(buf);
					std::vector<int> params;
				    params.push_back(cv::IMWRITE_JPEG_QUALITY);
				    cv::imwrite("/Users/ruhana/CAM2/Prototype-Controller/final.jpg", a, params);
				} 
			}		
	}
}


void Controller::read_video(string filename){

  cout << filename << endl;

    VideoCapture cap(filename); // open the default camera

//    VideoCapture cap(0);
    if(!cap.isOpened()){  // check if we succeeded
         cout << "It's not opening the file" << endl;
	 return;
    }
    Mat *group[this->groupSize];
   for(;;)

    {
	int groupNum = 0;
	//for(int i = 0; i < this->groupSize; i++){
        for(int i = 0; i < 30; i++){
	  int frameNum = 1;
	  int frameId = cap.get(frameNum++);
	  Mat *frame = new Mat();
          cap >> *frame; // get a new frame from camera
	  imshow("video", *frame);
	  group[i] = frame;
	}

	pthread_mutex_lock(&lock);
	//clips->push(*group);
	pthread_mutex_unlock(&lock);


	groupNum++;
	if(waitKey(5000) > 0)
		break;
      }

    thread0Finish = 1; // added to notify when read_video thread ends
 
}


void Controller::print_queue(queue<Mat*> *clips){
	cout << "Check queue by printing queue" << endl;
	Mat *a;

	int num = 0;
	for(int i = 0; i < clips->size(); i++) {
		a = clips->front();
		clips->pop();
		cout << a << endl;
	}
}
void Controller::receive(queue<string> msgs){

	if(msgs.size() == 0){

		cout << "There is no such message yet";
		return;
	}

	cout << "START RECEIVING MESSAGES" << endl;

	while(msgs.size()!=0){

		cout << msgs.front() << endl;
		msgs.pop();
	}
}

void Controller::start(){
		thread0Finish = 0;
		pthread_t sendThread;
		pthread_t readThread;
		
		int a = pthread_create(&sendThread, NULL, Controller::send_group_thread_callback, this);
		int b = pthread_create(&readThread, NULL, Controller::read_video_thread_callback, this);
		if (a == 0 || b == 0) {printf("Issue Creating Thread\n"); exit(1);}

		while(!thread0Finish) {
			pthread_create(&sendThread, NULL, Controller::send_group_thread_callback, this);
		} 
		//pthread_create(&sendThread, NULL, Controller::send_group_thread_callback, this);
		pthread_join(readThread, NULL); 
		pthread_join(sendThread, NULL);
		//pthread_exit(NULL);
}

void * Controller::send_group_thread_callback(void *controllerPtr) {
	Controller * controller = (Controller*) controllerPtr;
	controller->send_group();
	return controllerPtr;
}

void * Controller::read_video_thread_callback(void * controllerPtr) {
	Controller * controller = (Controller*) controllerPtr;
	//controller->read_video("file_name"); //uncomment this later!
	controller->push_test(); // place holder for now
	return controllerPtr;
}

void Controller::push_test() {
	for(int i = 0; i < 10; i++) {
		cv::Mat pic = cv::imread("/Users/ruhana/CAM2/Prototype-Controller/Version 2.jpg", CV_LOAD_IMAGE_COLOR);
		Mat * frames;
		frames = &pic; // pointer to single picture


		pthread_mutex_lock(&lock); // LOCK START ************************
		clips->push(frames); // add array to queue
		printf("#%lu ADDED\n", clips->size());
		pthread_mutex_unlock(&lock); // LOCK START ************************ 
	} 
	thread0Finish = 1;
}


