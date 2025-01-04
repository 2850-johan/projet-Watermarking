#include <opencv2/opencv.hpp>
#include "/home/nel/projet-Watermarking/tests/naomie.cpp"
#include "/home/nel/projet-Watermarking/tests/dec2bin.cpp"
#include "/home/nel/projet-Watermarking/tests/fresnel.cpp"
#include "/home/nel/projet-Watermarking/tests/lsbmodify.cpp"
#include "/home/nel/projet-Watermarking/tests/bin2dec.cpp"
#include "/home/nel/projet-Watermarking/tests/audiotodecimal.cpp"

using namespace std;
using namespace cv;

int main() {



    cout << "=== Menu Principal ===" << endl;
    cout << "1. Cacher une image dans une image" << endl;
    cout << "2. Cacher un fichier audio dans une image" << endl;
    cout << "3. Cacher un script dans une image" << endl;
    cout << "4.Extraire une donnée cachée" << endl;
    cout << "5:Stocker une donnée dans la bibliothèque"<<endl;
    cout << "0. Quitter" << endl;
    cout << "======================" << endl;
    cout << "Entrez votre choix : ";<<endl;

    int choix ; 
    cin >> choix;

    switch (choix)
    {

        case 1:
            /* Étape 1 : Extraction des valeurs de l'image à cacher */

        vector<int> imhide = extrairePixelValues("/home/nel/projet-Watermarking/Images/titre.jpeg");

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
        vector<int> imhote = extrairePixelValues("/home/nel/projet-Watermarking/Images/top-section-bg.jpeg");

        int tabhote = imhote.size();
    
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
        // Reconstruction de l'image à partir des valeurs binaires modifiées avec la fonction de Christian ensuite celle de Naomi sur le résiultat de cette fonction
         vector<int> decimalArray = binaryToDecimal(modifiedBitsValues);

        //Extraction de l'image cachée




         break ; 

     case 2:
        //vector<int> audiohide =  extraireDecimalValuesAudio("chemin d'acces de l'audio") ;

     
        break ;
     
    case 4:
        

        cout << "Quel type de donnée souhaitez vous extraire" << endl;
        cout << "1. Extraire une image " << endl;
        cout << "2. EXtraire un script " << endl;
        cout << "3.Extraire un fichier audio " << endl;
        cout << "0. Quitter" << endl;


       int choice ; 
       cout<<"Veuillez faire un choix: "<<endl.
       cin >> choice;

    switch (choice);
    {;
    case 1:
        cout<< "A:Choisir l'image à extraire pour vérification "<<endl;

      


        int choice1
        cout<<"Choisir une option"<<endl;
        cin >> choice1;
           vector<int> imhide = extrairePixelValues("/home/johan/Documents/Watermark/Images/titre.jpeg");

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

     



        cout<< "B:Choisir l'image hôte qui contient l'image cachée"<<endl;
        int choice2
        cout<<"Choisir une option"<<endl;
        cin >> choice2





        vector<int> imhote = extrairePixelValues("/home/johan/Documents/Watermark/Images/top-section-bg.jpeg");

        int tabhote = imhote.size();
    
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




       Mat hidenvalues=extract(uniqueColumn,binaryMatHote);

       Mat resizedhidenvalues=resizingextract(hidenvalues);



        /*Faire de sorte que l'utilisateur puisse parcourir pour choisir l'image et qu'on fixe l'ordre pour demander de choisir les 
        images

        */

/*
        if (choice1=="A") {

               vector<int> imhide = extrairePixelValues("/home/johan/Documents/Watermark/Images/titre.jpeg");

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

     


        }




 

        if (choice1=="B"){

            vector<int> imhote = extrairePixelValues("/home/johan/Documents/Watermark/Images/top-section-bg.jpeg");

        int tabhote = imhote.size();
    
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

        };


        */


        

        /*Reconstruire l'image à partir de là sachant qu'on a un tableau binaire à 8 colonnes à transformer en unique colonne décimale 
        puis en trois canaux puis en image */



    };
    



    case 0:
        cout << "Quitter le programme..." << endl;
        return 0;

    default:
        cout << "Choix invalide, réessayez." << endl;
        break;

    }

    return 0;

}
