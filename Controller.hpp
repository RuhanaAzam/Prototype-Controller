#include <opencv>
#include <queue>
#include <iostream>
#include <stdlib.h>
#include <string>

class Controller{

	private:
		ComUnit * cu; // communication unit
		int worker; // ???
		int groupSize; //number of frames 
		std::queue<int> seg; //video segmets
		//std::queue<cv::Mat*> segM; //video segmetent 30 frames each
//		Mat[] groups;
		queue<Mat[]> *clips;

	public:
		Controller(int worker, std::queue <int> seg); 
		void send_group();
		void read_video();
		void print_queue(std::queue<int> seg);
};


