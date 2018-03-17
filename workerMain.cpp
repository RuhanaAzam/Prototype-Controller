#include <cstdlib>
#include <iostream>
#include <thread>
#include "CommUnit.hpp"

using namespace std;

int main()
{
	try
	{
		char localPort[5] = {'2', '2', '2', '2', '\0'};
		char hostPort[5] = {'1', '1', '1', '1', '\0'};
		char hostIP[10] = {'1', '2', '7', '.', '0', '.', '0', '.', '1', '\0'};
		vector<ConnectionInfo*> v;
		ConnectionInfo* info = (ConnectionInfo*) malloc(sizeof(*info));
		if(info == NULL)
		{
			cout << "malloc failed\n";
			return EXIT_FAILURE;
		}
		info->localPort_ = localPort;
		info->hostPort_ = hostPort;
		info->hostIP_ = hostIP;
		v.push_back(info);
		StartTransport* cu = new StartTransport(v);
		thread t(&StartTransport::start, cu);
		t.join();
		free(info);
		delete(cu);
	}
	catch(exception& e)
	{
		cerr << "Exception: " << e.what() << "\n";
	}
	return EXIT_SUCCESS;
}
