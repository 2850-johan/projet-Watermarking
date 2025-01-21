#include <opencv2/opencv.hpp>
#include <string>
#include "/home/fresnel/Watermark/tests/AudioTransform.cpp"
#include "/home/fresnel/Watermark/tests/naomie.cpp"
#include "/home/fresnel/Watermark/tests/dec2bin.cpp"
#include "/home/fresnel/Watermark/tests/fresnel.cpp"
#include "/home/fresnel/Watermark/tests/lsbmodify.cpp"
#include "/home/fresnel/Watermark/tests/bin2dec.cpp"
#include "/home/fresnel/Watermark/tests/fonctioninverse_naomie.cpp"
#include "/home/fresnel/Watermark/tests/saveImage.cpp"




using namespace std;
using namespace cv;
/*
int main() {

        // Etape 1 :  extraction des valeurs binaires du fichier audio.
            vector<int> AudioHide = extraireDecimalValuesAudio("/home/fresnel/Watermark/tests/EricSkiff-Prologue.mp3");

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
                 vector<int> imhote = extrairePixelValues("/home/fresnel/Watermark/Images/top-section-bg.jpeg");
        
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
            cv::Mat imageOriginale = cv::imread("/home/fresnel/Watermark/Images/top-section-bg.jpeg");
            if (imageOriginale.empty()) {
                cerr << "Erreur : Impossible de charger l'image." << endl;
                return -1;
            }

            int largeur = imageOriginale.cols;
            int hauteur = imageOriginale.rows;

            vector<int> decimalArrayCombined =  binaryToDecimal(modifiedBitsValues);
            cv :: Mat imagefinal = reconstruireImage(decimalArrayCombined, largeur, hauteur);

        // Etape 9:  Sauvegarde de l'image final 

             string cheminversrep = "/home/fresnel/Watermark/Images";
            string nomfichierimgfinale = "img_modifiee_audio.jpeg";
            sauvegarderImage(imagefinal, cheminversrep, nomfichierimgfinale);

     return 0;
}*/



int main() {
    // Étape 1 : Extraction des valeurs binaires du fichier audio
    vector<int> AudioHide = extraireDecimalValuesAudio("/home/fresnel/Watermark/tests/EricSkiff-Prologue.mp3");
    if (AudioHide.empty()) {
        cerr << "Erreur : Impossible de lire le fichier audio." << endl;
        return -1;
    }

    // Étape 2 : Conversion en binaire
    vector<vector<int>> AudioValuesBinary = decimalToBinary(AudioHide);
    if (AudioValuesBinary.empty()) {
        cerr << "Erreur : La conversion en binaire a échoué." << endl;
        return -1;
    }

    // Étape 3 : Conversion en matrice OpenCV
    if (AudioValuesBinary.empty() || AudioValuesBinary[0].empty()) {
        cerr << "Erreur : Données binaires invalides pour le fichier audio." << endl;
        return -1;
    }
    Mat binaryAudioHide(AudioValuesBinary.size(), AudioValuesBinary[0].size(), CV_32S);
    for (int i = 0; i < AudioValuesBinary.size(); ++i) {
        for (int j = 0; j < AudioValuesBinary[i].size(); ++j) {
            binaryAudioHide.at<int>(i, j) = AudioValuesBinary[i][j];
        }
    }

    // Étape 4 : Transformation en colonne unique
    Mat uniqueColumnAudio = bintocol(binaryAudioHide);
    if (uniqueColumnAudio.empty()) {
        cerr << "Erreur : Impossible de transformer les données en colonne unique." << endl;
        return -1;
    }

    // Étape 5 : Extraction des valeurs binaires de l'image hôte
    vector<int> imhote = extrairePixelValues("/home/fresnel/Watermark/Images/top-section-bg.jpeg");
    if (imhote.empty()) {
        cerr << "Erreur : Impossible de lire l'image hôte." << endl;
        return -1;
    }

    // Étape 6 : Conversion en binaire et matrice
    vector<vector<int>> binvalhote = decimalToBinary(imhote);
    if (binvalhote.empty()) {
        cerr << "Erreur : La conversion en binaire pour l'image hôte a échoué." << endl;
        return -1;
    }
    Mat binaryMatHote(binvalhote.size(), binvalhote[0].size(), CV_32S);
    for (int i = 0; i < binvalhote.size(); ++i) {
        for (int j = 0; j < binvalhote[i].size(); ++j) {
            binaryMatHote.at<int>(i, j) = binvalhote[i][j];
        }
    }

    // Étape 7 : Remplacement des bits LSB
    Mat modifiedBitsValues = lsbreplace(uniqueColumnAudio, binaryMatHote);
    if (modifiedBitsValues.empty()) {
        cerr << "Erreur : Impossible de remplacer les bits LSB." << endl;
        return -1;
    }

    // Étape 8 : Reconstruction de l'image
    cv::Mat imageOriginale = cv::imread("/home/fresnel/Watermark/Images/top-section-bg.jpeg");
    if (imageOriginale.empty()) {
        cerr << "Erreur : Impossible de charger l'image originale." << endl;
        return -1;
    }

    int largeur = imageOriginale.cols;
    int hauteur = imageOriginale.rows;

    vector<int> decimalArrayCombined = binaryToDecimal(modifiedBitsValues);
    cv::Mat imagefinal = reconstruireImage(decimalArrayCombined, largeur, hauteur);
    if (imagefinal.empty()) {
        cerr << "Erreur : Impossible de reconstruire l'image." << endl;
        return -1;
    }

    // Étape 9 : Sauvegarde de l'image finale
    string cheminversrep = "/home/fresnel/Watermark/Images";
    string nomfichierimgfinale = "img_modifiee_audio.jpeg";
    sauvegarderImage(imagefinal, cheminversrep, nomfichierimgfinale);

    cout << "Image modifiée sauvegardée avec succès dans : " << cheminversrep << "/" << nomfichierimgfinale << endl;

    return 0;
}
