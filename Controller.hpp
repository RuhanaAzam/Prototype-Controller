#include "opencv2/opencv.hpp"
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <string>
#include "ComUnit.cpp"


using namespace std;
using namespace cv;
class Controller{


	private:
		ComUnit * cu; // communication unit
		int worker; // number of workers
		int groupSize; //number of frames 
		queue<Mat*> *clips;
		pthread_mutex_t lock;
		
		
	public:
		Controller(int worker, queue<Mat*> *clips, int groupSize);
		void send_group();
		void read_video(string filename);
		void push_test();
		void print_queue(queue<Mat*> *clips);
		void receive(queue<string> msgs);
		void start();

		int thread0Finish;
		static void * send_group_thread_callback(void *controllerPtr);
		static void * read_video_thread_callback(void * controllerPtr);
};




