#include <opencv2/opencv.hpp>  // Inclusion de la bibliothèque OpenCV
#include <iostream>            // Inclusion de la bibliothèque pour les entrées/sorties standard
#include <vector>    
using namespace std ;           // Pour utiliser std::vector

// Fonction pour extraire les valeurs décimales d'un fichier audio

std::vector<int> extraireDecimalValuesAudio(const std::string& cheminFichier) {
    // Déclare le vecteur qui contiendra les valeurs décimales de l'audio
    std::vector<int> DecimalAudioValues;

    std :: ifstream fichier ( cheminFichier, std ::ios::binary);
    if (! fichier.is_open()) // ouverture du fichier audio et on controlle s'il n'est pas vide.
      {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier audio : " << cheminFichier << std::endl;
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



    