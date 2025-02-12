#include "Textextract.h"

#include <bitset>
#include<string>
#include <filesystem>
#include <vector>


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


using namespace std;
using namespace cv;
using namespace std::filesystem;


string extractBitsAsString(const Mat& imageHost, int hiddenRows) {
    // Vérifier si la matrice est non vide
    if (imageHost.empty()) {
        cerr << "Erreur : La matrice imageHost est vide." << endl;
        return "";
    }

    // Vérifier si la matrice a une colonne au moins
    if (imageHost.cols < 1) {
        cerr << "Erreur : La matrice imageHost n'a pas assez de colonnes." << endl;
        return "";
    }

    // Cibler la dernière colonne
    Mat lsbcol = imageHost.col(imageHost.cols - 1);

    // Vérifier si la hauteur demandée est valide
    if (hiddenRows > lsbcol.rows) {
        cerr << "Erreur : La hauteur spécifiée dépasse la taille de la dernière colonne." << endl;
        return "";
    }

    // Extraire les bits dans la limite de `hiddenRows`
    string extractedBits = "";
    for (int i = 0; i < hiddenRows; ++i) {
        int bit = lsbcol.at<uchar>(i, 0) & 1; // Extraire le bit LSB
        extractedBits += to_string(bit);      // Ajouter le bit à la chaîne
    }

    return extractedBits;
}
