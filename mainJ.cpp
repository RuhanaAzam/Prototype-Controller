#include "Controller.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>
#include "opencv2/opencv.hpp"
//This main fucntion is for testing read_viode() function


using namespace std;
using namespace cv;
int main(int, char**){


  string filename = "1.mp4";
  int groupSize = 30;
  queue<vector<Mat>>* clips = new queue<vector<Mat>>();
  Controller *controller = new Controller(3,clips,5);
  



  controller->start();


  queue<string> msgs;

  //msgs.push("It's connected");
  //msgs.push("It is groupting");
  //msgs.push("It was created already");
  //controller->receive(msgs);



//  delete clips;
//  delete controller;

}
