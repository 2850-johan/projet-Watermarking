#include <opencv2/opencv.hpp>
#include "/home/nel/Watermark/tests/AudioTransform.cpp"
#include "/home/nel/Watermark/tests/dec2bin.cpp"
#include "/home/nel/Watermark/tests/fresnel.cpp"
#include "/home/nel/Watermark/tests/lsbmodify.cpp"
#include "/home/nel/Watermark/tests/bin2dec.cpp"
#include "/home/nel/Watermark/tests/fonctioninverse_naomie.cpp"
#include "/home/nel/Watermark/tests/saveImage.cpp"


using namespace std;
using namespace cv;

int main() {

        // Etape 1 :  extraction des valeurs binaires du fichier audio.
            vector<int> AudioHide = extraireDecimalValuesAudio("chemin du fichier audio");

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
                 vector<int> imhote = extrairePixelValues("chemin de l'image");
        
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
            cv::Mat imageOriginale = cv::imread("/home/nel/Watermark/Images/titre.jpeg");
            if (imageOriginale.empty()) {
                cerr << "Erreur : Impossible de charger l'image." << endl;
                return -1;
            }

            int largeur = imageOriginale.cols;
            int hauteur = imageOriginale.rows;

            vector<int> decimalArrayCombined =  binaryToDecimal(modifiedBitsValues);
            cv :: Mat imagefinal = reconstruireImage(decimalArrayCombined, largeur, hauteur);

        // Etape 9:  Sauvegarde de l'image final 

             string cheminversrep = "chemin de où il irra ";
            string nomfichierimgfinale = "img_extraite.jpeg";
            sauvegarderImage(imagefinal, cheminversrep, nomfichierimgfinale);

     return 0;
}