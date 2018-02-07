#include<cstdio>
#include "ComUnit.cpp"
#include <queue>

class Controller{
	private:
		ComUnit * cu; // communication unit
		int worker; // ???
		std::queue<> seg; //video segmets

	public:
		Controller(int worker, std::queue <int> seg); 
		void send_group();
		void read_video();
};

Controller::Controller(int worker, std::queue <int> seg) // constructor
{
	this->worker = worker;
	this->seg = seg;
	cu = new ComUnit;
} 

void Controller::send_group(){
	int clip = seg.pop();
	printf("%s %d\n", "send_group done", cu->sent("asdas"));
}

void Controller::read_video(){}

int main() {
	printf("Hello World!\n");
	std::queue <int> seg;
	seg.push(5);
	seg.push(6);
	seg.push(7);
	Controller * c = new Controller(4,seg);
	c->send_group();
	
	return 1;
}