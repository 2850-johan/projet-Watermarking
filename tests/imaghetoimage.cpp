#include <iostream>
#include <opencv2/opencv.hpp>



#include <bitset>
using namespace std;
using namespace cv;

int main() {



    Mat imagehide= imread("home/fresnel/Documents/Watermark/Image/imagehide.jpeg");
    if (imagehide.empty()) {
        cerr << "Erreur lors du chargement de l'image." << endl;
        return -1;
    }

 

    //Création d'un tableau pour stocker les valeurs binaire de chaque pixel de l'image ,la taille du tableau binaire est défini en multipliant le nombre de lignes par le nombre de colones par le nombre de canaux (RVB)
 int taille=imagehide.cols*imagehide.rows*3;

 vector<bitset<8>> binary(taille);




for (int y = 0; y < imagehide.rows; y++) {
    for (int x = 0; x < imagehide.cols; x++) {
        
            
             Vec3b pixel = imagehide.at<Vec3b>(y, x);

           

             // Transformer chaque composante en binaire et les stocker dans binary
             /*y imagehide.cols+x  sert à définir l'index du pixel dans
              le tableau binary (y étant le numéro de ligne ,
                imagehide.cols le nombre de colones donne le nombre
                 de pixel par ligne et *3 permet de réserver une plage de 3
                  pour les valeurs RVB notamment,dans le tableau binary,+0/1/2 sert à dire que 
                  c'est réservé à telle valeur de couleur)*/
             //pixel[0] sert à recuperer la valeur de couleur dont il s'agit dans le pixel concerné 

        binary[(y * imagehide.cols + x) * 3 + 0] = bitset<8>(pixel[0]); // Composante bleue
        binary[(y * imagehide.cols + x) * 3 + 1] = bitset<8>(pixel[1]); // Composante verte
        binary[(y * imagehide.cols + x) * 3 + 2] = bitset<8>(pixel[2]); // Composante rouge


        };
    };


 
    // Concaténer l'ensemble des bits dans la variable
    string variable;
    for (int i = 0; i < taille; i++) {
        variable += binary[i].to_string();
    }

    cout << "Message binaire : " << variable << endl;

/*ostringstream oss;
for (int i = 0; i < taille; i++) {
    oss << binary[i].to_string();
}
string variable = oss.str();
*/









	  Mat image = imread("home/fresnel/Documents/Watermark/Image/image.jpeg");
    if (image.empty()) {
        cerr << "Erreur lors du chargement de l'image." << endl;
        return -1;
    }

    int t = variable.length();  // Longueur totale de la chaîne binaire
    int n = 0;  // Indice de bit dans le message





    if (image.cols * image.rows * 3 >=variable.length()) {
    

 for (int y = 0; y < image.rows; y++){
    for (int x = 0; x < image.cols; x++) {
        
            if (n < t) {  // Vérifie s'il reste des bits à insérer
                Vec3b pixel = image.at<Vec3b>(y, x);  // Récupère le pixel (format BGR)

                // Modifie le bit de poids faible de la composante rouge en fonction du bit du message
                if (variable[n] == '1') {
                    pixel[2] = pixel[2] | 1;  // Met le LSB à 1 si le bit du message est '1'
                } else {
                    pixel[2] = pixel[2] & ~1;  // Met le LSB à 0 si le bit du message est '0'
                }

                // Met à jour le pixel avec le rouge modifié
                image.at<Vec3b>(y, x) = pixel;
                n++;  // Passe au bit suivant
            }
        }
    }

}

else {

    cerr << "L'image hôte est trop petite pour contenir l'image cachée." << endl;
    return -1;
}


    // Sauvegarde de l'image modifiée
    bool savedimage = imwrite("home/fresnel/Documents/Watermark/Image/imagemodifiee.jpeg", image);
    if (!savedimage) {
        cerr << "Erreur lors de la sauvegarde de l'image." << endl;
        return -1;
    }

    // Affichage de l'image modifiée
    
   
    imshow("Image modifiée", image);
    waitKey(0);

    return 0;
}