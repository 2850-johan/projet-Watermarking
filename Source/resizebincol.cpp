#include "resizebincol.h"
#include <opencv2/opencv.hpp> 
#include <iostream>

using namespace std;
using namespace cv;
//Fonction de redimensionnement en matrice binaire de 8 colonnes des bits cachés extraits


Mat resizingextract(Mat& uchiden) {
    int elementsize = uchiden.rows * uchiden.cols;

    if (elementsize % 8 != 0) {
        cerr << "Erreur : Le tableau binaire à colonne unique de l'image cachée ne peut pas être réorganisé en 8 colonnes." << endl;
        return Mat();
    }

    if (!uchiden.isContinuous()) {
        uchiden = uchiden.clone();
    }

    return uchiden.reshape(1, elementsize / 8);
};


















