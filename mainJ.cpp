#include "Controller.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "opencv2/opencv.hpp"
#include "CommUnit.hpp"
//This main fucntion is for testing read_viode() function


using namespace std;
using namespace cv;
int main(int, char**){


	//local ports for each ServerUnit to use
        static char local1_[5] = {'9','9','9','2','\0'};
        //static char local2_[5] = {'9','9','9','3','\0'};
        //static char local3_[5] = {'9','9','9','4','\0'};

        //host ports for each ClientUnit to connect to
        static char worker1_[5] = {'3','1','1','2','\0'};
        //static char worker2_[5] = {'4','1','1','2','\0'};
        //static char worker3_[5] = {'5','1','1','2','\0'};

        //local ip address
        static char workerIP1_[10] ={'1','2','7','.','0','.','0','.','1','\0'};
        static char workerIP2_[10] ={'1','2','7','.','0','.','0','.','1','\0'};
        static char workerIP3_[10] ={'1','2','7','.','0','.','0','.','1','\0'};

        std::vector<ConnectionInfo*> v;
        ConnectionInfo *temp = (ConnectionInfo *)malloc(sizeof(ConnectionInfo));
        temp -> hostIP_ = workerIP1_;
        temp -> hostPort_ = worker1_;
        temp -> localPort_ = local1_;

        v.push_back(temp);

      


  	string filename = "1.mp4";
  	int groupSize = 30;
  	queue<vector<Mat>>* clips = new queue<vector<Mat>>();
  	StartTransport * cu = new StartTransport(v);
	Controller *controller = new Controller(3,clips,5,cu);
  



  controller->start();


  queue<string> msgs;

  //msgs.push("It's connected");
  //msgs.push("It is groupting");
  //msgs.push("It was created already");
  //controller->receive(msgs);



//  delete clips;
//  delete controller;

}
