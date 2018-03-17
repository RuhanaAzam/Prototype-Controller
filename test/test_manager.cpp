//#include <cstdlib>
#include <iostream>
//#include <queue>
#include <stdlib.h>
#include <string>
#include <thread>
//#include "asio.hpp"
#include "CommUnit.hpp"
#include "Controller.hpp"
#include "opencv2/opencv.hpp"
//#include "queue.hpp"

//using asio::ip::tcp;
using namespace std;
using namespace cv;

int main(int argc, char* argv[])
{
  try
  {
/*    if (argc != 4)
    {
      cerr << "Usage: test_manager <local port> <host port> <host IP>\n";
      return EXIT_FAILURE;
    }*/

    vector<ConnectionInfo*> v;
    ConnectionInfo* info = (ConnectionInfo*) malloc(sizeof(ConnectionInfo));
    if(info == NULL)
    {
      cout << "malloc failed\n";
      return EXIT_FAILURE;
    }
    char localPort[5] = {'1', '1', '1', '1', '\0'};
    char hostPort[5] = {'2', '2', '2', '2', '\0'};
    char hostIP[10] = {'1', '2', '7', '.', '0', '.', '0', '.', '1', '\0'};
    info->localPort_ = localPort;
    info->hostPort_ = hostPort;
    info->hostIP_ = hostIP;
    v.push_back(info);
    StartTransport* cu = new StartTransport(v);
    string videoName = "1.mp4";
    int groupSize = 30;
    queue<vector<Mat>>* clips = new queue<vector<Mat>>();
    Controller* controller = new Controller(3, clips, 300, cu);
    thread t1(&StartTransport::start, cu);
    thread t2(&Controller::start, controller);
/*    char line[18];
    for(int i = 0; i < 1000; i++)
    {
      sprintf(line, "./tosend/9%03d.png", i);
      FILE* fp = fopen(line, "r");
      if(fp == NULL)
      {
        cout << "fopen failed\n";
        cout << "filename = " << line << "\n";
        break;
      }
      fseek(fp, 0, SEEK_END);
      unsigned int filesize = ftell(fp);
      fseek(fp, 0, SEEK_SET);
      MessageInfo * msg = (MessageInfo *) malloc(sizeof(*msg));
      msg->size_ = filesize;
      msg->msg_ = (char*) malloc(sizeof(*(msg->msg_)) * msg->size_);
      fread(msg->msg_, sizeof(char), msg->size_, fp);
      fclose(fp);
      cu->outQueue.push(msg);
    } */
    t1.join();
    t2.join();
    free(info);
    delete(cu);
    delete(clips);
    delete(controller);
  }
  catch (exception& e)
  {
    cerr << "Exception: " << e.what() << "\n";
  }
  return EXIT_SUCCESS;
}
