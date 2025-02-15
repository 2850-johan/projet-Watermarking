#include "extracthidenbincol.h"
#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace std;
using namespace cv;



//Fonction pour extraire la colonne unique binaire de l'image cachée

Mat extract(const Mat& imagehidein, int hiddenRows) {
    // Cibler la dernière colonne, la colonne des LSB de l'image hôte
    Mat lsbcol = imagehidein.col(imagehidein.cols - 1).clone();

    // Vérifier si la hauteur demandée est valide
    if (hiddenRows > lsbcol.rows) {
        cerr << "Erreur : La hauteur spécifiée pour les données extraites dépasse la taille de la dernière colonne." << endl;
        return Mat();
    };



// Extraire la partie correspondant à la taille de uniqueColumn
Mat extractedPart = lsbcol.rowRange(0, hiddenRows).clone();



   return extractedPart;



}















/*
Mat  extract(Mat& imagehideuc ,Mat&imagehidein) {


//Cibler la dernière colonne,la colonne des lsb de l'image hôte
Mat lsbcol=imagehidein.col(imagehidein.cols-1).clone();
int hidenheight=imagehideuc.rows*imagehideuc.cols;
Mat hidenbytes=lsbcol.rowRange(0,hidenheight);


if (hidenheight > lsbcol.rows){

	cerr<<"L'image n'est pas cachée dans l'image hôte";
	return Mat();
};



return hidenbytes;



}


*/














/*
Mat extract(Mat& imagehideuc, Mat& imagehidein) {
    // Cibler la dernière colonne, la colonne des LSB de l'image hôte
    Mat lsbcol = imagehidein.col(imagehidein.cols - 1).clone();
    
    // Calculer le nombre total de pixels dans l'image cachée
    int hidenheight = imagehideuc.rows * imagehideuc.cols;

    // Vérifier si l'image cachée peut être extraite
    if (hidenheight > lsbcol.rows) {
        cerr << "Erreur : L'image cachée est trop grande ou n'existe pas dans l'image hôte." << endl;
        return Mat();
    }

    // Extraire les données correspondantes
    Mat hidenbytes = lsbcol.rowRange(0, hidenheight).clone();

    return hidenbytes;
}



*/














/*






int main() {
    // Créer une matrice "image hôte" (valeurs décimales)
    Mat imageHost = (Mat_<uchar>(8, 4) << 
        12, 34, 56, 78,
        23, 45, 67, 89,
        34, 56, 78, 90,
        45, 67, 89, 12,
        56, 78, 90, 23,
        67, 89, 12, 34,
        78, 90, 23, 45,
        89, 12, 34, 56);

    // Créer une matrice "image cachée" (valeurs décimales)
    Mat imageToHide = (Mat_<uchar>(4, 1) << 
        1, 
        2, 
        3, 
        4);

    cout << "Matrice hôte (image hôte) :" << endl << imageHost << endl;
    cout << "Matrice cachée (image cachée) :" << endl << imageToHide << endl;

    // Tester la fonction extract
    Mat extractedData = extract(imageToHide, imageHost);

    if (extractedData.empty()) {
        cerr << "Erreur : Les données extraites sont vides." << endl;
        return -1;
    }

    // Afficher les données extraites
    cout << "Matrice extraite :" << endl << extractedData << endl;

    return 0;
}














*/









