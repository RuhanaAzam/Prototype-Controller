#include "Controller.hpp"
#include "matSerial.cpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
#include <vector>
#include <pthread.h>
#include <bitset>
#inlcude "CommUnit.hpp"
using namespace cv;
using namespace std;
 
//#include "opencv2/core/mat.hpp"
//#include "opencv2/core.hpp"'
#include "opencv2/opencv.hpp"




Controller::Controller(int worker, queue<vector<Mat> > *clips, int groupSize, StartTransport * cu) // constructor
{
	this->worker = worker;
	this->groupSize = groupSize;
	this->clips = clips;
	this->cu = cu;
	messageID = 0;
} 


void Controller::send_group(){
	while(1) { 


		lock.lock();
		//pthread_mutex_lock(&lock); // LOCK START ************************
		if(clips->empty()) { // exits function when empty
			//cout << "Queue Empty" << endl;
			lock.unlock();
			//pthread_mutex_unlock(&lock); // LOCK END**********************
			break;


		} else {

			vector<Mat> frames;
			//printf("%d\t", clips->empty());
			frames = clips->front();
			clips->pop();
			printf("#%d REMOVED : \n", index/30);
			
			//pthread_mutex_unlock(&lock); // LOCK END**********************
			lock.unlock();
			

			for(int i = 0; i < (groupSize); i++) { // sending 30 frames one by one
				vector<unsigned char> buf = matWrite(frames[i]);
				//cu->sent(buf); // send to comUnit

				// ADDED FOR VERIFICATION // REMOVE LATER
				cv::Mat a = matRead(buf);
				std::vector<int> params;
				params.push_back(cv::IMWRITE_JPEG_QUALITY);
				params.push_back(90);
				char buff [strlen("/home/nvidia/jisoo/Prototype-Controller/image_out/final.jpg") + 1];
				sprintf(buff,"/home/nvidia/jisoo/Prototype-Controller/image_out/final%d.jpg", index);
				index++;
				cv::imwrite(buff, a, params);
			}
			
			
		}		
	}
}


void Controller::read_video(string filename){

    VideoCapture cap(filename); // open the default camera

    if(!cap.isOpened()){  // check if we succeeded
         cout << "It's not opening the file" << endl;
	 return;
    }
   vector<Mat> group;

   Mat frame;
   //namedWindow("w",1);
   for(;;)

    {
	int groupNum = 0;
	//for(int i = 0; i < this->groupSize; i++){
        for(int i = 0; i < 30; i++){
	  int frameNum = 1;
	  int frameId = cap.get(frameNum++);
	  //frame = new Mat();
          cap >> frame; // get a new frame from camera
	 // imshow("video", *frame);
	 //cout << frameNum << endl;
	  group.push_back(frame);
        }

	//pthread_mutex_lock(&lock);
    	lock.lock();
    	clips->push(group);
	printf("#%lu Reading the video\n", clips->size());


	lock.unlock();
//	cout << "OUTSIDE?" << endl;
	groupNum++;
	


	if(waitKey(30) >= 0)
		break;
	}
	thread0Finish = 1; // added to notify when read_video thread ends
}




void Controller::print_queue(queue<vector<Mat> > *clips){
	cout << "Check queue by printing queue" << endl;
	vector<Mat> a;

	int num = 0;
	for(int i = 0; i < clips->size(); i++) {
		a = clips->front();
		clips->pop();
		cout << i << endl;
	}

}
void Controller::receive(queue<string> msgs){

	if(msgs.size() == 0){

		cout << "There is no such message yet";
		return;
	}


	cout << "START RECEIVING MESSAGES" << endl;


	while(msgs.size()!=0){

		messageID++;
		bitset<32> num(messageID);
		cout << num  << " | " <<msgs.front() << endl;
		msgs.pop();
	}
}

void Controller::start(){
		index = 0;
		thread0Finish = 0;
		pthread_t sendThread;
		pthread_t readThread;
		
		int a = pthread_create(&sendThread, NULL, Controller::send_group_thread_callback, this);
		int b = pthread_create(&readThread, NULL, Controller::read_video_thread_callback, this);
		if (a == -1 || b == -1) {printf("Issue Creating Thread %d %d\n",a,b); exit(1);}

		while(!thread0Finish) {
			pthread_create(&sendThread, NULL, Controller::send_group_thread_callback, this);
		} 
		pthread_create(&sendThread, NULL, Controller::send_group_thread_callback, this);
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
	controller->read_video("1.mp4"); //uncomment this later!
	//controller->push_test(); // place holder for now
	return controllerPtr;
}

void Controller::push_test() {
	cv::Mat pic = cv::imread("/Users/ruhana/CAM2/Prototype-Controller/Version 2.jpg", CV_LOAD_IMAGE_COLOR);
	for(int i = 0; i < 10; i++) {
		std::vector<cv::Mat> frames;
		//pthread_mutex_lock(&lock);
		lock.lock();
		for(int i = 0 ; i < groupSize; i++) {
			frames.push_back(pic.clone());
		}
		//pthread_mutex_lock(&lock); // LOCK START ************************
		clips->push(frames); // add array to queue
		//pthread_mutex_unlock(&lock); // LOCK END*************************
		printf("#%lu ADDED\n", clips->size());
		lock.unlock();
		
	} 
	thread0Finish = 1;
}

/*
Controller::~Controller(){


	delete cu;

}
*/
