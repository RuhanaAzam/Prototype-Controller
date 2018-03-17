#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include "CommUnit.hpp"
#include "Controller.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

int main()
{
	try
	{
		//local ports for each ServerUnit to use
		char local1_[5] = {'9','9','9','2','\0'};
		//static char local2_[5] = {'9','9','9','3','\0'};
		//static char local3_[5] = {'9','9','9','4','\0'};
	
		//host ports for each ClientUnit to connect to
		char worker1_[5] = {'3','1','1','2','\0'};
		//static char worker2_[5] = {'4','1','1','2','\0'};
		//static char worker3_[5] = {'5','1','1','2','\0'};
	
		//local ip address
		char workerIP1_[10] ={'1','2','7','.','0','.','0','.','1','\0'};
		char workerIP2_[10] ={'1','2','7','.','0','.','0','.','1','\0'};
		char workerIP3_[10] ={'1','2','7','.','0','.','0','.','1','\0'};
	
		vector<ConnectionInfo*> v;
		ConnectionInfo *temp = (ConnectionInfo *)malloc(sizeof(ConnectionInfo));
		if(temp == NULL)
		{
			cout << "malloc failed\n";
			return EXIT_FAILURE;
		}
		temp -> hostIP_ = workerIP1_;
		temp -> hostPort_ = worker1_;
		temp -> localPort_ = local1_;
	
		v.push_back(temp);
	
		StartTransport* cu = new StartTransport(v);
		string videoName = "1.mp4";
		int groupSize = 30;
		queue<vector<Mat>>* clips = new queue<vector<Mat>>();
		Controller* controller = new Controller(3, clips, 300, cu);
		thread t1(&StartTransport::start, cu);
		thread t2(&Controller::start, controller);
		t1.join();
		t2.join();
		free(temp);
		delete(cu);
		delete(clips);
		delete(controller);
	}
	catch(exception& e)
	{
		cerr << "Exception: " << e.what() << "\n";
	}
	return EXIT_SUCCESS;
}
