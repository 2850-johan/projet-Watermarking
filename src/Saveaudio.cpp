#include <opencv2/opencv.hpp> 
#include <iostream>            
#include <fstream>             // Pour lire et écrire des fichiers
#include <vector>             

using namespace std;
using namespace cv;


// Fonction pour écrire les octets extraits dans un fichier audio
void sauvegarderAudio(const string& cheminFichier, const vector<unsigned char>& audioData) {
    ofstream fichier(cheminFichier, ios::binary);  // Ouvre un fichier binaire
    if (!fichier) {
        cerr << "Erreur : Impossible de créer le fichier audio !" << endl;
        return;
    }

    // Écrit les octets dans le fichier
    fichier.write(reinterpret_cast<const char*>(audioData.data()), audioData.size());
    fichier.close();  
    cout << "Extraction réussie ! Fichier audio sauvegardé : " << cheminFichier << endl;
}

