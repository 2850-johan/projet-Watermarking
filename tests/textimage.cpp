#include <iostream>
#include <opencv2/opencv.hpp>


#include <cstring>  // Nécessaire pour utiliser strlen avec un tableau de caractères
#include <bitset>
using namespace std;
using namespace cv;

int main() {
    char message[] = "Bonjour";
    
    int taille = strlen(message);  // Utilisation de strlen pour obtenir la taille du tableau de caractères

    int array[taille];

    // Transformer le message en son code ASCII
    for (int i = 0; i < taille; i++) {
        array[i] = int(message[i]);
    }

    // Transformer le code ASCII en binaire et le stocker dans le tableau binary
    bitset<8> binary[taille];
    for (int i = 0; i < taille; i++) {
        binary[i] = bitset<8>(array[i]);
    }

    // Concaténer l'ensemble des bits dans la variable
    string variable;
    for (int i = 0; i < taille; i++) {
        variable += binary[i].to_string();
    }

    cout << "Message binaire : " << variable << endl;

    Mat image = imread("Documents/Watermark/Image/image.jpeg");
    if (image.empty()) {
        cerr << "Erreur lors du chargement de l'image." << endl;
        return -1;
    }

    int t = variable.length();  // Longueur totale de la chaîne binaire
    int n = 0;  // Indice de bit dans le message

    for (int x = 0; x < image.cols; x++) {
        for (int y = 0; y < image.rows; y++) {
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

    // Sauvegarde de l'image modifiée
    bool savedimage = imwrite("Documents/Watermark/Image/imagemodifiee.jpeg", image);
    if (!savedimage) {
        cerr << "Erreur lors de la sauvegarde de l'image." << endl;
        return -1;
    }

    // Affichage de l'image modifiée
    Mat imagemodif = imread("Documents/Watermark/Image/imagemodifiee.jpeg");
    if (imagemodif.empty()) {
        cerr << "Erreur lors du chargement de l'image modifiée." << endl;
        return -1;
    }
    imshow("Image modifiée", imagemodif);
    waitKey(0);

    return 0;
}
