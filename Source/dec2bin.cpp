#include "dec2bin.h"
#include <iostream>
using namespace std;


vector<vector<int>> decimalToBinary(const vector<int>& arr) {

    // Taille du vecteur d'entrée
    int nbre_lignes = arr.size(); 
    // Initialisation du tableau binaire
    vector<vector<int>> array_binary(nbre_lignes, vector<int>(8, 0)); 
    

    // Poids pour remplir de droite à gauche
    for (int i = 0; i < nbre_lignes; i++) {
        int poids = 7; 
        int valeur_decimal = arr[i]; // Récupérer la valeur décimale

        while (valeur_decimal > 0) {
            array_binary[i][poids] = valeur_decimal % 2; // Récupération du bit de poids faible
            valeur_decimal /= 2; // Division par 2
            poids--; // Aller au bit suivant
        }
    }

    return array_binary;
}

