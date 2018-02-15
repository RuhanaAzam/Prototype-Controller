#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace cv;

vector<unsigned char> matWrite(const Mat& mat)
{

    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    cv::imwrite("/Users/ruhana/CAM2/Prototype-Controller/writeFram.jpeg", mat, params);

    IplImage* fIplImageHeader;
    fIplImageHeader = cvCreateImageHeader(cvSize(mat.rows, mat.cols), IPL_DEPTH_8U, mat.channels());
    vector<unsigned char> buf;
    cv::imencode(".jpeg", _InputArray(mat), buf ,params);
    return buf;
}


Mat matRead(vector<unsigned char> buf)
{
    cv::Mat a = cv::imdecode(buf, CV_LOAD_IMAGE_ANYDEPTH);
    return a;
}



