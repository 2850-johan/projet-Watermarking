#include <opencv2/opencv.hpp> 
#include <iostream>           
#include <fstream>             
#include <vector>              

using namespace std;
using namespace cv;

// Fonction pour extraire les bits de poids faible (LSB) des pixels de l'image
vector<int> extraireBitsLSB(const Mat& image) {
    vector<int> bitsLSB;  // Stocke les bits extraits

    // Parcourt chaque pixel de l'image
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            int pixelValue = image.at<uchar>(i, j);  // Récupère la valeur du pixel
            bitsLSB.push_back(pixelValue & 1);  // Extrait le dernier bit (LSB)
        }
    }
    return bitsLSB;  // Retourne les bits extraits
}