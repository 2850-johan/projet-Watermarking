#ifndef LSBAUDIO_H
#define LSBAUDIO_H

#include <opencv2/opencv.hpp> 
#include <iostream>           
#include <fstream>             
#include <vector>              

using namespace std;
using namespace cv;
vector<int> extraireBitsLSB(const Mat& image) ;

#endif;