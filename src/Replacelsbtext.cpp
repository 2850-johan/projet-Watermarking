#include "Replacelsbtext.h"

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


Mat replaceBitsInLastColumn(const string& binaryData, Mat& imageHost) {
    // Vérification des entrées
    if (imageHost.empty()) {
        cerr << "Erreur : La matrice imageHost est vide." << endl;
        return Mat();
    }

    if (binaryData.empty()) {
        cerr << "Erreur : La chaîne binaire binaryData est vide." << endl;
        return Mat();
    }

    // Vérification que les données binaires tiennent dans la dernière colonne
    if ((int)binaryData.size() > imageHost.rows) {
        cerr << "Erreur : La chaîne binaire est trop grande pour être insérée dans la dernière colonne." << endl;
        return Mat();
    }

    // Parcourir les bits de la chaîne et les insérer dans la dernière colonne
    for (int i = 0; i < (int)binaryData.size(); ++i) {
        int bit = binaryData[i] - '0'; // Convertir le caractère '0' ou '1' en entier
        if (bit != 0 && bit != 1) {
            cerr << "Erreur : La chaîne contient des caractères non binaires." << endl;
            return Mat();
        }

        // Remplacer le bit dans la dernière colonne
        imageHost.at<int>(i, imageHost.cols - 1) = bit;
    }

    cout << "Les bits ont été insérés avec succès dans la dernière colonne." << endl;
    return imageHost;
}
