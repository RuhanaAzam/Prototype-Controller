#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

vector<unsigned char> matWrite(const Mat& mat)
{

    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    vector<unsigned char> buf;
    cv::imencode(".jpg", _InputArray(mat), buf ,params);
    return buf;
}


Mat matRead(vector<unsigned char> buf)
{
    cv::Mat a = cv::imdecode(buf, CV_LOAD_IMAGE_COLOR);
    return a;
}



