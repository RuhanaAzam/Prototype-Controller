#include<cstdio>
#include "ComUnit.cpp"
#include <queue>
#include "opencv2/core/mat.hpp"
#include "opencv2/core.hpp"'
#include <opencv2/opencv.hpp>

class Controller{
	private:
		ComUnit * cu; // communication unit
		int worker; // ???
		std::queue<int> seg; //video segmets
		//std::queue<cv::Mat*> segM; //video segmetent 30 frames each

	public:
		Controller(int worker, std::queue <int> seg); 
		void send_group();
		void read_video();
		void print_queue(std::queue<int> seg);
};

Controller::Controller(int worker, std::queue <int> seg) // constructor
{
	this->worker = worker;
	this->seg = seg;
	cu = new ComUnit;
	cv::Mat x(10, 10, CV_8UC1);
} 

void Controller::send_group(){
	printf("%s\n", "send_group done");
}

void Controller::read_video(){}
void Controller::print_queue(std::queue<int> seg){
	int a;
	for(int i = 0; i < seg.size(); i++) {
		a = seg.front();
		seg.pop();
		printf("%d\n", a);
		seg.push(a);
	}
}

