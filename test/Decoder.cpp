#include <cstdlib>
#include <iostream>
#include <vector>
#include "Decoder.hpp"
#include "matSerial.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

void Decoder::decode(long msgsize, char* data, int index)
{
	vector<unsigned char> buf;
	for(int i = 0; i < msgsize; i++)
	{
		buf.push_back(data[i]);
	}
	cv::Mat a = matRead(buf);
	std::vector<int> params;
	params.push_back(cv::IMWRITE_JPEG_QUALITY);
	params.push_back(90);
	char line[19];
	sprintf(line, "./received/%03d.jpg", index);
	cv::imwrite(line, a, params);
}
