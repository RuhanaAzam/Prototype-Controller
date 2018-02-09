

#include "Controller.hpp"
//This main fucntion is for testing read_viode() function

int main(int, char**){

  string filename = "1.mp4";
  int groupSize = 30;
  Controller *controller = new Controller();
  controller -> read_video(filename,groupSize);



}
