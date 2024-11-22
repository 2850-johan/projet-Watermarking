#include <iostream>
#include <cmath> // Pour utiliser la fonction pow

using namespace std;

// Fonction pour convertir un tableau binaire en décimal
void binaryToDecimal(int array_binary[][8], int nbre_lignes) 
{
    int array_decimal[nbre_lignes][1]; // Tableau pour stocker les valeurs décimales

    for (int i = 0; i < nbre_lignes; i++) 
    {
        int decimal = 0; // Initialiser la valeur décimale à 0 pour chaque ligne

        // ici on parcours chaque colonne du tableau binaire 
        for (int j = 0; j < 8; j++) 
        {
            decimal += array_binary[i][j] * pow(2, 7 - j); // a*2^poids
        }

        array_decimal[i][0] = decimal; // Stocker la valeur décimale dans le tableau

        // Affichage de la conversion
       // cout << "Binaire : ";
        for (int j = 0; j < 8; j++) 
        {
           // cout << array_binary[i][j];
        }
        cout  << decimal << endl;
    }
}



/*int main()
{
     // Définir un tableau binaire à convertir en décimal
    int nbre_lignes = 4;
    int array_binary[4][8] = {
        {0, 0, 0, 0, 1, 1, 0, 1}, // 13 
        {0, 0, 1, 0, 1, 1, 0, 1}, // 45 
        {0, 0, 0, 0, 0, 1, 1, 1}, // 7 
        {1, 0, 0, 0, 0, 0, 0, 0}  // 128 
    };

    // Appeler la fonction pour convertir en décimal
    binaryToDecimal(array_binary, nbre_lignes);


          return 0;
     
}
