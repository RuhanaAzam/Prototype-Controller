#include <iostream>
#include <stdlib.h>
#include <string>
#include "opencv2/opencv.hpp"
#include "CommUnit.hpp"
#include "Controller.hpp"
#include "matSerial.hpp"
#include <pthread.h>
#include <thread>
//This main fucntion is for testing read_viode() function


using namespace std;
using namespace cv;

void printResults(StartTransport * s){
// ADDED FOR VERIFICATION // REMOVE LATER	
	
	MessageInfo *msgInfo_ = s -> inQueue.pop();
	
	std::vector<unsigned char> buf(msgInfo_ -> size_);
	
	std::memcpy(buf.data(), msgInfo_ -> msg_, msgInfo_ -> size_);
	cv::Mat a = matRead(buf);
	std::vector<int> params;
	params.push_back(cv::IMWRITE_JPEG_QUALITY);
	params.push_back(90);
	std::cout << "Writting to file" << std::endl;
	//cv::imshow("window", a);
	cv::imwrite("output/o1.jpg", a);
	std::cout << "file written" << std::endl;
}
int main(int, char**){


	//local ports for each ServerUnit to use
        static char local1_[5] = {'5','0','0','6','\0'};
        //static char local2_[5] = {'9','9','9','3','\0'};
        //static char local3_[5] = {'9','9','9','4','\0'};

        //host ports for each ClientUnit to connect to
        static char worker1_[5] = {'5','0','0','7','\0'};
        //static char worker2_[5] = {'4','1','1','2','\0'};
        //static char worker3_[5] = {'5','1','1','2','\0'};

        //local ip address
//        static char workerIP1_[13] ={'1','9','2','.','1','6','8','.','1','.', '5', '1','\0'};
        static char workerIP2_[10] ={'1','2','7','.','0','.','0','.','1','\0'};
        static char workerIP3_[10] ={'1','2','7','.','0','.','0','.','1','\0'};

        std::vector<ConnectionInfo*> v;
        ConnectionInfo *temp = (ConnectionInfo *)malloc(sizeof(ConnectionInfo));
        temp -> hostIP_ = workerIP2_;
        temp -> hostPort_ = worker1_;
        temp -> localPort_ = local1_;

        v.push_back(temp);

	StartTransport * s = new StartTransport(v);      
	std::thread t1 = std::thread(&StartTransport::start, s);
	std::thread t2 = std::thread(printResults, s);
	
	t2.join();
	t1.join();


}
