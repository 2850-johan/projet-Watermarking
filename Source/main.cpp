#include <opencv2/opencv.hpp>
#include <bitset>
#include <filesystem>
#include <vector>
#include <string>
#include <iostream>
#include <fstream> 
#include "include/Audiotodec.h"
#include "include/bin2dec.h"
#include "include/binarytoText.h"
#include "include/Bintocol.h"
#include "include/dec2bin.h"
#include "include/extracthidenbincol.h"
#include "include/lsbmodify.h"
#include "include/Movefiletobiblio.h"
#include "include/Pixelstocol.h"
#include "include/Reconstructimage.h"
#include "include/Replacelsbtext.h"
#include "include/resizebincol.h"
#include "include/saveImage.h"
#include "include/Textextract.h"
#include "include/lsbaudio.h"
#include "include/Saveaudio.h"
#include "include/bintodecaudio.h"
using namespace std;
using namespace cv;
using namespace std::filesystem;





//Variable globale pour stockage de la matrice binaire de l'image hôte qui contiendra le texte à cacher
Mat im;

int main() 

{
   int choix;

   while(true) {

    cout << "=== Menu Principal ===" << endl;
    cout << "1. Cacher une image dans une image" << endl;
    cout << "2. Cacher un audio dans une image" << endl;
    cout << "3. Cacher un texte dans une image" << endl;
    cout << "4. Extraire une donnée cachée" << endl;
    cout << "5. Stocker une donnée dans la bibliothèque" << endl;
    cout << "0. Quitter" << endl;
    cout << "======================" << endl;

    
    cout << "Entrez votre choix : "<<endl;;
    cin >> choix;

    switch (choix) {
        case 1: {
            // Étape 1 : Transformation de l'image à cacher en vecteur décimal
            vector<int> imhide = extrairePixelValues("Biblio/titre.jpeg");

            // Étape 2 : Conversion de l'image à cacher de ses valeurs décimales à celles binaires
            vector<vector<int>> binaryval = decimalToBinary(imhide);

            // Étape 3 : Conversion du vecteur en Matrice opencv
            Mat binaryMatHide = Mat(binaryval.size(), binaryval[0].size(), CV_32S);
            for (int i = 0; i < binaryval.size(); ++i) {
                for (int j = 0; j < binaryval[i].size(); ++j) {
                    binaryMatHide.at<int>(i, j) = binaryval[i][j];
                }
            }

            // Étape 4 : Transformation de la matrice en colonne unique
            Mat uniqueColumn = bintocol(binaryMatHide);

            // Étape 5 : Transformation de l'image hôte en vecteur décimal
            vector<int> imhote = extrairePixelValues("Biblio/top-section-bg.jpeg");

            // Étape 6 : Conversion en binaire et matrice
            vector<vector<int>> binvalhote = decimalToBinary(imhote);
            Mat binaryMatHote = Mat(binvalhote.size(), binvalhote[0].size(), CV_32S);
            for (int i = 0; i < binvalhote.size(); ++i) {
                for (int j = 0; j < binvalhote[i].size(); ++j) {
                    binaryMatHote.at<int>(i, j) = binvalhote[i][j];
                }
            }

            // Étape 7 : Remplacement des bits LSB
            Mat modifiedBitsValues = lsbreplace(uniqueColumn, binaryMatHote);

            // Étape 8 : Reconstruction de l'image modifiée
            cv::Mat imageOriginale = cv::imread("Biblio/top-section-bg.jpeg");
            if (imageOriginale.empty()) {
                cerr << "Erreur : Impossible de charger l'image originale." << endl;
                return -1;
            }

            int largeur = imageOriginale.cols;
            int hauteur = imageOriginale.rows;
            vector<int> decimalArray = binaryToDecimal(modifiedBitsValues);
            cv::Mat image = reconstruireImage(decimalArray, largeur, hauteur);

            // Étape 9 : Sauvegarde de l'image
            string cheminversrep = "Biblio";
            string nomfichierimgfinale = "img_modifiee.jpeg";
            sauvegarderImage(image, cheminversrep, nomfichierimgfinale);
            break;
        };

        case 2: {
            cout << "Cacher un fichier audio dans une image" << endl;
            

        // Etape 1 :  extraction des valeurs binaires du fichier audio.
            string cheminFichier = "Biblio/EricSkiff-Prologue.mp3"; 
            vector<int> AudioHide = extraireDecimalValuesAudio(cheminFichier);

        // Etape 2 : Conversion des valeurs decimales contenues dans le vecteur pour les binaires sur 8 bits.
             vector<vector<int>> AudioValuesBinary = decimalToBinary(AudioHide);

         // Etape intermédiaire ( on porte les valeurs du vecteur AudioValuesBinary qu'on transporte dans la matrice BinaryAudioHide)
            Mat binaryAudioHide = Mat(AudioValuesBinary.size(), AudioValuesBinary[0].size(), CV_32S);
            for (int  i = 0; i < AudioValuesBinary.size(); ++i)
            {
                for (int  j = 0; j < AudioValuesBinary[i].size(); ++j)
                {
                binaryAudioHide.at<int>(i,j) = AudioValuesBinary[i][j];
                }
                
            }
        
        // Etape 4 : Transformation en colonne unique des valeurs en binaire de la matrice  binaryAudioHide
            Mat uniqueColumnAudio = bintocol(binaryAudioHide);

        // Etape 5 : extraction des valeurs binaires de l'image qui recoit le fichier audio
                 vector<int> imhote = extrairePixelValues("Biblio/top-section-bg.jpeg");
        
        // Etape 6 : Conversion des valeurs decimales contenues dans le vecteur pour les binaires sur 8 bits.
              vector<vector<int>> binvalhote = decimalToBinary(imhote);

              Mat binaryMatHote = Mat(binvalhote.size(), binvalhote[0].size(), CV_32S);
              for (int i = 0; i < binvalhote.size(); ++i)
               {
                for (int j = 0; j < binvalhote[i].size(); ++j)
                 {
                    binaryMatHote.at<int>(i, j) = binvalhote[i][j];
                }
               }

        // Etape 7 : Remplacement des bits LSB
            Mat modifiedBitsValues = lsbreplace(uniqueColumnAudio, binaryMatHote) ;

        //Etape 8 : Reconstruction de l'image 
            Mat imageOriginale = cv::imread("Biblio/top-section-bg.jpeg");
            if (imageOriginale.empty()) {
                cerr << "Erreur : Impossible de charger l'image." << endl;
                return -1;
            }

            int largeur = imageOriginale.cols;
            int hauteur = imageOriginale.rows;

            vector<int> decimalArrayCombined =  binaryToDecimal(modifiedBitsValues);
             Mat imagefinal = reconstruireImage(decimalArrayCombined, largeur, hauteur);

        // Etape 9:  Sauvegarde de l'image final 

             string cheminversrep = "Biblio";
            string nomfichierimgfinale = "img_modif_audio.jpeg";
            sauvegarderImage(imagefinal, cheminversrep, nomfichierimgfinale);

         cout<<"Audio caché avec succès"<<endl;

         break;
        };
    

        case 3: {
          cout << "Cacher un texte saisi dans une image " << endl;

    // Saisie du texte
    string message;
    cout << "Veuillez saisir le texte à cacher : ";
    cin.ignore();
    getline(cin, message);

    // Conversion du texte en binaire
    string variable;
    for (char c : message) {
        bitset<8> binaryChar(c);
        variable += binaryChar.to_string(); // Concaténer chaque caractère binaire
    }

    // Étape 5 : Extraction des valeurs décimales de l'image hôte
    vector<int> imhote = extrairePixelValues("Biblio/titre.jpeg");
    if (imhote.empty()) {
        cerr << "Erreur : Impossible d'extraire les pixels de l'image hôte." << endl;
        return -1;
    }

    // Étape 6 : Conversion en binaire et création de la matrice
    vector<vector<int>> binvalhote = decimalToBinary(imhote);
    Mat binaryMatHote(binvalhote.size(), binvalhote[0].size(), CV_32S);
    for (int i = 0; i < binvalhote.size(); ++i) {
        for (int j = 0; j < binvalhote[i].size(); ++j) {
            binaryMatHote.at<int>(i, j) = binvalhote[i][j];
        }
    }

    // Remplacement des bits LSB avec la variable binaire
     im = replaceBitsInLastColumn(variable, binaryMatHote);
    if (im.empty()) {
        cerr << "Erreur : Problème lors du remplacement des bits LSB." << endl;
        return -1;
    }

    // Charger l'image originale pour récupérer ses dimensions
    Mat imageOriginale = imread("Biblio/titre.jpeg");
    if (imageOriginale.empty()) {
        cerr << "Erreur : Impossible de charger l'image originale." << endl;
        return -1;
    }

    int largeur = imageOriginale.cols;
    int hauteur = imageOriginale.rows;

    // Reconstruction de l'image à partir des valeurs binaires modifiées
    vector<int> decimalArray = binaryToDecimal(im);
    Mat image = reconstruireImage(decimalArray, largeur, hauteur);
    if (image.empty()) {
        cerr << "Erreur : Impossible de reconstruire l'image." << endl;
        return -1;
    }

    // Sauvegarde de l'image modifiée
    string cheminversrep = "Biblio";
    string nomfichierimgfinale = "img_texte_cachee.jpeg";
    sauvegarderImage(image, cheminversrep, nomfichierimgfinale);

    cout << "Image modifiée et sauvegardée avec succès dans : " << cheminversrep << "/" << nomfichierimgfinale << endl;


            break;
        };

        case 4: {
            cout << "Quel type de donnée souhaitez-vous extraire ?" << endl;
            cout << "1. Extraire une image" << endl;
            cout << "2. Extraire un texte" << endl;
            cout << "3. Extraire un fichier audio" << endl;
            cout << "0. Quitter" << endl;

            int choice;
            cout << "Veuillez faire un choix : ";
            cin >> choice;

            switch (choice) {
                case 1: {
                // Extraction de l'image cachée

    // Étape 1 : Extraction des valeurs en décimal de l'image censée être cachée
    vector<int> imhide = extrairePixelValues("Biblio/titre.jpeg");
    if (imhide.empty()) {
        cerr << "Erreur : Impossible de lire les pixels de l'image à cacher." << endl;
        return -1;
    }

    // Étape 2 : Conversion en valeurs binaires (tableau binaire)
    vector<vector<int>> binaryval = decimalToBinary(imhide);
    if (binaryval.empty()) {
        cerr << "Erreur : La conversion en binaire a échoué." << endl;
        return -1;
    }

    // Étape 3 : Conversion en matrice OpenCV
    Mat binaryMatHide(binaryval.size(), binaryval[0].size(), CV_32S);
    for (int i = 0; i < binaryval.size(); ++i) {
        for (int j = 0; j < binaryval[i].size(); ++j) {
            binaryMatHide.at<int>(i, j) = binaryval[i][j];
        }
    }

    // Étape 4 : Transformation en une matrice colonne unique
    Mat uniqueColumn = bintocol(binaryMatHide);
    if (uniqueColumn.empty()) {
        cerr << "Erreur : Impossible de transformer les valeurs en colonne unique." << endl;
        return -1;
    }



     //Détermination de la taille de la matrice à colonne unique censée être cachée
    int rowscoluc = uniqueColumn.rows*uniqueColumn.cols;

    // Étape 5 : Extraction des valeurs de l'image modifiée
    vector<int> imhotes = extrairePixelValues("Biblio/img_modifiee.jpeg");
    if (imhotes.empty()) {
        cerr << "Erreur : Impossible de lire les pixels de l'image modifiée." << endl;
        return -1;
    }

  

     vector<int> imhote = extrairePixelValues("Biblio/top-section-bg.jpeg");

            // Étape 6 : Conversion en binaire et matrice
            vector<vector<int>> binvalhote = decimalToBinary(imhote);
            Mat binaryMatHote = Mat(binvalhote.size(), binvalhote[0].size(), CV_32S);
            for (int i = 0; i < binvalhote.size(); ++i) {
                for (int j = 0; j < binvalhote[i].size(); ++j) {
                    binaryMatHote.at<int>(i, j) = binvalhote[i][j];
                }
            }

            Mat modifiedBitsValues = lsbreplace(uniqueColumn, binaryMatHote);


    
    Mat hidenvalues = extract(modifiedBitsValues, rowscoluc);
    if (hidenvalues.empty()) {
        cerr << "Erreur : Impossible d'extraire les bits cachés." << endl;
        return -1;
    }
   

    // Étape 8 : Redimensionner les valeurs extraites
    Mat resizedhidenvalues = resizingextract(hidenvalues);
    if (resizedhidenvalues.empty()) {
        cerr << "Erreur : Impossible de redimensionner les valeurs extraites." << endl;
        return -1;
    }

    // Étape 9 : Reconstruction de l'image extraite
    Mat imageOriginale = imread("Biblio/titre.jpeg");
    if (imageOriginale.empty()) {
        cerr << "Erreur : Impossible de charger l'image originale." << endl;
        return -1;
    }

    int largeur = imageOriginale.cols;
    int hauteur = imageOriginale.rows;

//Étape 9.1: Transformation des valeurs en valeurs décimales(vecteur décimal) 
    vector<int> decimalArray = binaryToDecimal(resizedhidenvalues);
    Mat image = reconstruireImage(decimalArray, largeur, hauteur);

    if (image.empty()) {
        cerr << "Erreur : Impossible de reconstruire l'image." << endl;
        return -1;
    }

    // Étape 10 : Sauvegarde de l'image extraite
    string cheminversrep = "Biblio";
    string nomfichierimgfinale = "img_cachee_extraite.jpeg";
    sauvegarderImage(image, cheminversrep, nomfichierimgfinale);

    cout << "Image extraite et sauvegardée avec succès dans : " << cheminversrep << "/" << nomfichierimgfinale << endl;

  break;


};
             case 2:{
                    cout << "Extraction d'un texte " << endl;


                
    // Saisie du texte
    string message;
    cout << "Veuillez saisir le texte censé être cachée pour récupération de sa taille : ";
    cin.ignore();
    getline(cin, message);

    // Conversion du texte en binaire
    string variable;
    for (char c : message) {
        bitset<8> binaryChar(c);
        variable += binaryChar.to_string(); // Concaténer chaque caractère binaire
    }

   vector<int> imhotem = extrairePixelValues("Biblio/img_texte_cachee.jpeg");

            // Étape 6 : Conversion en binaire et matrice
            vector<vector<int>> binvalhotem = decimalToBinary(imhotem);
            Mat binaryMatHotem = Mat(binvalhotem.size(), binvalhotem[0].size(), CV_32S);
            for (int i = 0; i < binvalhotem.size(); ++i) {
                for (int j = 0; j < binvalhotem[i].size(); ++j) {
                    binaryMatHotem.at<int>(i, j) = binvalhotem[i][j];
                }
            }


            string variable1=extractBitsAsString(im,(int)variable.size());



            string mess =binaryToText(variable1);

            cout<<"Le message caché est : "<<mess<<endl;



            

                    break;

                };

               

                case 3:{
                    cout << "Extraction d'un fichier audio " << endl;
     // Chemin de l'image contenant l'audio caché
               string cheminImage = "Biblio/img_modif_audio.jpeg";

   
                 Mat imageModifiee = imread(cheminImage, IMREAD_GRAYSCALE);
                 if (imageModifiee.empty()) {
              cerr << "Erreur : Impossible de charger l'image." << endl;
            return -1;
               }

    // Extraire les bits LSB 
                 vector<int> bitsLSB = extraireBitsLSB(imageModifiee);

    // Convertir les bits extraits en valeurs décimales (octets)
                vector<unsigned char> audioData = bitsToDecimal(bitsLSB);

    // Sauvegarder les données extraites dans un fichier audio
           string cheminFichierAudio = "Biblio/fichier_extrait.mp3";
          sauvegarderAudio(cheminFichierAudio, audioData);
                    break;
}
                case 0:
                    cout << "Quitter le menu d'extraction." << endl;
                    break;

                default:
                    cout << "Choix invalide. Veuillez réessayer." << endl;
                    break;
            }
            break;
        }

        case 5: {
            cout << "Stockage d'une image dans la bibliothèque " << endl;
            string cheminSource;
           string repertoireCible = "Biblio"; // Répertoire par défaut pour stocker les fichiers

        // Effacer le buffer cin avant de lire une nouvelle entrée
          cin.ignore(numeric_limits<streamsize>::max(), '\n');


          cout << "Entrez le chemin du fichier à déplacer : ";
          getline(cin, cheminSource);

  
         deplacerFichier(cheminSource, repertoireCible);

    break; 
}
        case 0:
            cout << "Quitter le programme. À bientôt !" << endl;
            return 0;

        default:
            cout << "Choix invalide. Veuillez réessayer." << endl;
            break;
    }
}

    return 0;
}
