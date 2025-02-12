#include "Bintocol.h"
#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace cv;
using namespace std;

Mat bintocol (const Mat& tableauBinaire)
{ 
 


    // Transformer la matrice en une seule colonne avec reshape(1,...)


    Mat colonneUnique = tableauBinaire.reshape(1, tableauBinaire.rows * tableauBinaire.cols);
    


return colonneUnique ; 
 };