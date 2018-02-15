#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace cv;

void matwrite(const string& filename, const Mat& mat)
{
      /* std::string str;
    int type = mat.type();
    int channels = mat.channels();
    int rows = mat.rows;
    int cols = mat.cols;
    str.append(std::to_string(mat.rows));
    str.append("\n");
    str.append(std::to_string(mat.cols));
    str.append("\n");
    str.append(std::to_string(mat.type()));
    str.append("\n");
    str.append(std::to_string(mat.channels()));
    str.append("\n");

    if (mat.isContinuous())
    {
        str.append(reinterpret_cast<char *>(mat.data));
        str.append("\n");
    }
    else
    {
        int rowsz = CV_ELEM_SIZE(type) * mat.cols;
        for (int r = 0; r < mat.rows; ++r)
        {
            str.append(reinterpret_cast<char *>(mat.data));
            str.append("\n");
        }
    } 
    //printf("%s\n", str.c_str());
    return str; */

    ofstream fs(filename, fstream::binary);

    // Header
    int type = mat.type();
    int channels = mat.channels();
    fs.write((char*)&mat.rows, sizeof(int));    // rows
    fs.write((char*)&mat.cols, sizeof(int));    // cols
    fs.write((char*)&type, sizeof(int));        // type
    fs.write((char*)&channels, sizeof(int));    // channels

    // Data
    if (mat.isContinuous())
    {
        fs.write(mat.ptr<char>(0), (mat.dataend - mat.datastart));
    }
    else
    {
        int rowsz = CV_ELEM_SIZE(type) * mat.cols;
        for (int r = 0; r < mat.rows; ++r)
        {
            fs.write(mat.ptr<char>(r), rowsz);
        }
    }
}


Mat matread(const string& filename)
{
      /* int rows, cols, type, channels;
    std::string data;

    std::string read = str.substr(0,1);
    int index = 0;
    str.erase(0,1); 
     while(!str.empty()) {
        while(read.back() != '\n') {
            read.append(str.substr(0,1));
            str.erase(0,1);
        }
        if(index == 0) {rows = stoi(read);}
        else if(index == 1) {cols = stoi(read);}
        else if(index == 2) {type = stoi(read);}
        else if(index == 3) {channels = stoi(read);}
        else { // for data
            data.append(read);
        }
        read.clear();
        index ++; 
     }   
           
        cv::Mat mat(rows,cols,type, reinterpret_cast<unsigned char *>(const_cast<char*>(data.c_str())), 0); // 0 = AUTO_STEP
   
    //printf("%d, %d, %d, %d, %s\n", rows, cols, type, channels, data.c_str());
    return mat; */
    ifstream fs(filename, fstream::binary);

    // Header
    int rows, cols, type, channels;
    fs.read((char*)&rows, sizeof(int));         // rows
    fs.read((char*)&cols, sizeof(int));         // cols
    fs.read((char*)&type, sizeof(int));         // type
    fs.read((char*)&channels, sizeof(int));     // channels

    // Data
    Mat mat(rows, cols, type);
    fs.read((char*)mat.data, CV_ELEM_SIZE(type) * rows * cols);

    return mat;
}
