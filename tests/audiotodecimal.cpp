// #include <opencv2/opencv.hpp>  // Inclusion de la bibliothèque OpenCV
#include <iostream>            // Inclusion de la bibliothèque pour les entrées/sorties standard
#include <vector>    
using namespace std ;           // Pour utiliser std::vector

// Fonction pour extraire les valeurs décimales d'un fichier audio
vector<int> extraireDecimalValuesAudio(const string& cheminAudio) {
    // Vecteur pour stocker les valeurs décimales extraites
    vector<int> audioData; // vecteur qui contien les valeur decimal de l'audio

    // Ouverture du fichier en mode binaire
    ifstream file(cheminAudio, ios::binary);
    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier audio !" << endl;
        return {}; // Retourne un vecteur vide en cas d'échec
    }

    // Ici on commence par ouvrir le fichier et convertir chaque octect en decimal 
    char buffer; // Buffer pour stocker chaque octet temporairement
    while (file.read(&buffer, sizeof(buffer)))  // a l'aide de la variable buffer qui est chargé de prendre une valeur la stocker temporaire puis la mettre dans le vecteur .
    {
        // Conversion de l'octet (en binaire) en entier non signé (décimal)
        audioData.push_back(static_cast<unsigned char>(buffer));
    }

    // Vérification si la lecture a échoué (autre qu'à la fin du fichier)
    if (file.bad()) {
        cerr << "Erreur : Échec de lecture du fichier audio !" << endl;
        return {};
    }

    // Fermeture du fichier audio
    file.close();

    return audioData; // Retourne le vecteur des valeurs décimales
}