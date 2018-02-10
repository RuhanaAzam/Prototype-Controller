#include<cstdio>
#include "ComUnit.cpp"
#include <queue>
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
	this->seg = seg;
	cu = new ComUnit;
} 

void Controller::send_group(){
	cv::Mat * frames = seg.front();
	seg.pop();

	matwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram.jpeg", frames[0]);
	matwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram2.jpeg", frames[1]);
	//for(int i = 0; i < sizeof(frames); i++) {
	//	matwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram", frames[i]);
	//}
	
	//const char * writeAddress = "/Users/ruhana/CAM2/Prototype-Controller/writeFram.jpg";
	//cv::Mat x = matread("/Users/ruhana/CAM2/Prototype-Controller/writeFram.jpg");

	// uploading jpeg as MAT
	// *** READ AND WRITE COLOR NOT DONE!!
	
// FOR JPEG CONVERSION
 	/*std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY );
	cv::imwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram", x, params); */

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

