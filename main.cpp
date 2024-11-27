#include <opencv2/opencv.hpp>
#include "/home/johan/Documents/Watermark/tests/naomie.cpp"
#include "/home/johan/Documents/Watermark/tests/dec2bin.cpp"
#include "/home/johan/Documents/Watermark/tests/fresnel.cpp"
#include "/home/johan/Documents/Watermark/tests/lsbmodify.cpp"

using namespace std;
using namespace cv;

int main() {

    /* Étape 1 : Extraction des valeurs de l'image à cacher */

    vector<int> imhide = extrairePixelValues("/home/johan/Documents/Watermark/Images/titre.jpeg");

    // Calcul de la taille du tableau
 //   int tailleTableau = imhide.size();
// ajout code ce matin 25/11/2024
  /*   int tableau[tailleTableau][1];
     for (int i = 0; i < tailleTableau; i++) 
     {
        tableau[i][0] = imhide[i];
    }*/
    // Conversion en valeurs binaires (tableau binaire)
    //vector<vector<int>> binaryval = decimalToBinary(imhide);ajout code ce matin 25/11/2024
    vector<vector<int>> binaryval= decimalToBinary(imhide) ;
    // conversion tab---> mat

    Mat binaryMatHide = Mat(binaryval.size(), binaryval[0].size(), CV_32S);
    for (int i = 0; i < binaryval.size(); ++i) {
        for (int j = 0; j < binaryval[i].size(); ++j) {
            binaryMatHide.at<int>(i, j) = binaryval[i][j];
        }
    }


    // Transformation du tableau binaire en une matrice colonne unique
    Mat uniqueColumn = bintocol(binaryMatHide);

    /* Étape 2 : Extraction des valeurs de l'image hôte */
    vector<int> imhote = extrairePixelValues("/home/johan/Documents/Watermark/Images/top-section-bg.jpeg");

    int tabhote = imhote.size();
// ajout code ce matin 25/11/2024
  /*   int tableauhote[tabhote][1];
     for (int i = 0; i < tabhote; i++)
     {
        tableauhote[i][0] = imhote[i];
    }*/


   /*  if (tabhote <= 0) {
        cout << "Erreur : Taille de tableau invalide." << endl;
        return -1;
    }

    // Utilisation d'un vector dynamique
    vector<vector<int>> tableauhote(tabhote, vector<int>(1));
    for (int i = 0; i < tabhote; i++) {
        tableauhote[i][0] = imhote[i];
    }*/

    /*// Affichage pour vérifier
    for (int i = 0; i < tabhote; i++) {
        cout << "tableauhote[" << i << "][0] = " << tableauhote[i][0] << endl;
    }

    return 0;*/
    // Conversion en valeurs binaires (tableau binaire)
   //vector<vector<int>> binaryval = decimalToBinary(imhide);ajout code ce matin 25/11/2024
    vector<vector<int>> binvalhote= decimalToBinary(imhote);
    // conversion tab---> mat

    // Transformation du tableau binaire de l'image hôte en matrice OpenCV
    Mat binaryMatHote = Mat(binvalhote.size(), binvalhote[0].size(), CV_32S);
    for (int i = 0; i < binvalhote.size(); ++i) {
        for (int j = 0; j < binvalhote[i].size(); ++j) {
            binaryMatHote.at<int>(i, j) = binvalhote[i][j];
        }
    }

    //Étape 3 : Remplacement des bits LSB 
    Mat modifiedBitsValues = lsbreplace(uniqueColumn, binaryMatHote);

    //Étape 4 : Reconstruction de l'image modifiée 
    // Reconstruction de l'image à partir des valeurs binaires modifiées



// Sauvegarde de l'image reconstruite
if (!imwrite("/home/johan/Documents/Watermark/Images/image_finale.jpg", reconstructedImage)) {
    cerr << "Erreur : L'image n'a pas été sauvegardée." << endl;
    return -1;
}

cout << "Image reconstruite et sauvegardée avec succès : image_finale.jpg" << endl;



   
    return 0;

}
