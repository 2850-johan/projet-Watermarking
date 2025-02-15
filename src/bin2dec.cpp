#include "bin2dec.h"
#include <iostream>
#include <vector>
#include <stdexcept> 
//#include <opencv2/opencv.hpp> 


using namespace std;
//using namespace cv;

vector<int> binaryToDecimal(const Mat& binaryMatrix) {
   
    if (binaryMatrix.empty()) {
        throw invalid_argument("La matrice binaire est vide !");
    }

    // Vérifier que la matrice a 8 colonnes
    if (binaryMatrix.cols != 8) {
        throw invalid_argument("Chaque ligne de la matrice doit contenir exactement 8 bits !");
    }

   
    vector<int> decimalArray(binaryMatrix.rows, 0);

    // Parcourir chaque ligne
    for (int i = 0; i < binaryMatrix.rows; i++) {
        int decimalValue = 0; // Valeur décimale pour la ligne actuelle

        // Parcourir chaque colonne
        for (int j = 0; j < binaryMatrix.cols; j++) {
            int bit = binaryMatrix.at<int>(i, j);

            // Vérifier que le bit est valide (0 ou 1)
            if (bit != 0 && bit != 1) {
                throw invalid_argument("Les valeurs de la matrice doivent être 0 ou 1 uniquement !");
            }

            // Ajouter la contribution de ce bit à la valeur décimale
            decimalValue = (decimalValue << 1) | bit; 
        }

        decimalArray[i] = decimalValue; 
    }

    return decimalArray;
}


























/*
int main() {
    try {
        // Étape 1 : Créer une matrice binaire pour le test
        Mat binaryMatrix = (Mat_<int>(4, 8) << 
            1, 0, 0, 0, 0, 0, 0, 1,  // Décimal : 129
            1, 1, 1, 1, 1, 1, 1, 0,  // Décimal : 254
            0, 0, 0, 0, 1, 0, 1, 1,  // Décimal : 11
            1, 0, 1, 0, 1, 0, 1, 0   // Décimal : 170
        );

        cout << "Matrice binaire initiale :" << endl << binaryMatrix << endl;

        // Étape 2 : Conversion de la matrice binaire en valeurs décimales
        vector<int> decimalArray = binaryToDecimal(binaryMatrix);
        cout << "Valeurs décimales extraites :" << endl;
        for (int value : decimalArray) {
            cout << value << " ";
        }
        cout << endl;

        // Étape 3 : Reconvertir les valeurs décimales en binaire
        vector<vector<int>> binaryMatrixReconstructed = decimalToBinary(decimalArray);

        // Conversion du tableau 2D en Matrice OpenCV pour affichage
        Mat reconstructedBinaryMatrix(binaryMatrixReconstructed.size(), binaryMatrixReconstructed[0].size(), CV_32S);
        for (size_t i = 0; i < binaryMatrixReconstructed.size(); ++i) {
            for (size_t j = 0; j < binaryMatrixReconstructed[i].size(); ++j) {
                reconstructedBinaryMatrix.at<int>(i, j) = binaryMatrixReconstructed[i][j];
            }
        }

        cout << "Matrice binaire reconstruite à partir des valeurs décimales :" << endl << reconstructedBinaryMatrix << endl;

        // Étape 4 : Vérification de la cohérence
        if (countNonZero(binaryMatrix != reconstructedBinaryMatrix) == 0) {
            cout << "Test réussi : La matrice initiale et reconstruite sont identiques." << endl;
        } else {
            cout << "Erreur : La matrice initiale et reconstruite ne sont pas identiques." << endl;
        }

    } catch (const exception& e) {
        cerr << "Exception : " << e.what() << endl;
    }

    return 0;
}
*/