#include <ctime>
#include <iostream>
#include <string>
#include <mutex>
#include <queue>
#include <thread>
#include <ctime>
#include "asio.hpp"
#include "queue.hpp"
#include "commUnit.hpp"


static void testQueue(Queue<char *> &outQueue){
	int i = 0;
	for ( i = 0; i < 1000; i++){
	for ( i = 0; i < 1000000; i++){
	char *tst = (char *)malloc(sizeof(char)*7);
	sprintf(tst, "%4d", i);
	outQueue.push(tst);
}
int main(){

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
	temp -> hostIP_ = workerIP1;
	temp -> hostPort_ = worker1_;
	temp -> localPort_ = local1_;
	
	v.push_back(temp);
	
	StartTransport s(v);



	
}
