#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace cv;
using namespace std;



Mat resizingextract(Mat& uchiden) {

int elementsize=uchiden.rows*uchiden.cols;

if (elementsize % 8 != 0) {

	cerr<<"Le tableau binaire à colonne unique de l'image cachée ne peut pas être réorganisé en 8 colonnes";

	return -1;

};

Mat resizedextract=uchiden.reshape(1,elementsize/8);
    

    return resizedextract;
};