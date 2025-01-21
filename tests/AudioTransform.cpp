/*#include <opencv2/opencv.hpp>  // Inclusion de la bibliothèque OpenCV
#include <iostream>            // Inclusion de la bibliothèque pour les entrées/sorties standard
#include <vector>    
using namespace std ;  
      // Pour utiliser std::vector

// Fonction pour extraire les valeurs décimales d'un fichier audio

vector<int> extraireDecimalValuesAudio(const string& cheminFichier) {
    // Déclare le vecteur qui contiendra les valeurs décimales de l'audio
    vector<int> DecimalAudioValues;

    ifstream fichier ( cheminFichier, ios::binary);
    if (! fichier.is_open()) // ouverture du fichier audio et on controlle s'il n'est pas vide.
      {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier audio : " << cheminFichier << endl;
        return DecimalAudioValues; // Retourne un vecteur vide
      }


    char octet; // cette variable permet de lire chaque octect depuis le fichier 
    while (fichier.read(&octet, sizeof(char))) // Stocke cet octet  dans la variable octet qui est char car peut contenir -128 à 128 
    {
        // Convertir chaque octet en entier et l'ajouter au vecteur DecimalAudioValues
        DecimalAudioValues.push_back(static_cast<unsigned char>(octet)); //ici on s'assure une conversion en  garantissant que les valeurs sont entre 0 et 255. 
    }

     fichier.close();  

    return DecimalAudioValues; // Retourne le vecteur des valeurs décimales

}
*/


#include <vector>
   #include <fstream>
   #include <iostream>

   std::vector<int> extraireDecimalValuesAudio(const std::string& cheminFichier) {
       std::vector<int> DecimalAudioValues;
       std::ifstream fichier(cheminFichier, std::ios::binary);
       if (!fichier.is_open()) {
           std::cerr << "Erreur : Impossible d'ouvrir le fichier audio : " << cheminFichier << std::endl;
           return DecimalAudioValues;
       }

       char octet;
       while (fichier.read(&octet, sizeof(char))) {
           DecimalAudioValues.push_back(static_cast<unsigned char>(octet));
       }

       fichier.close();
       return DecimalAudioValues;
   }








/*

#include <opencv2/opencv.hpp>  // Inclusion de la bibliothèque OpenCV
#include <iostream>            // Inclusion de la bibliothèque pour les entrées/sorties standard
#include <vector>              // Pour utiliser std::vector
#include <fstream>             // Pour les opérations sur les fichiers

using namespace std;           // Utilisation de l'espace de noms std

// Fonction pour extraire les valeurs décimales d'un fichier audio
vector<int> extraireDecimalValuesAudio(const string& cheminFichier) {
    // Déclare le vecteur qui contiendra les valeurs décimales de l'audio
    vector<int> DecimalAudioValues;

    // Ouvrir le fichier en mode binaire
    ifstream fichier(cheminFichier, ios::binary);
    if (!fichier.is_open()) { // Vérifie si le fichier ne s'est pas ouvert correctement
        cerr << "Erreur : Impossible d'ouvrir le fichier audio : " << cheminFichier << endl;
        return DecimalAudioValues; // Retourne un vecteur vide en cas d'erreur
    }

    // Variable pour stocker chaque octet lu depuis le fichier
    char octet;
    while (fichier.read(&octet, sizeof(char))) {
        // Convertir chaque octet en entier non signé et l'ajouter au vecteur DecimalAudioValues
        DecimalAudioValues.push_back(static_cast<unsigned char>(octet));
    }

    // Fermer le fichier après lecture
    fichier.close();

    return DecimalAudioValues; // Retourne le vecteur contenant les valeurs décimales
}




*/










    