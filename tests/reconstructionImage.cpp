#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "/home/nel/Watermark/tests/extractionLSB.cpp"



// Fonction pour reconstruire l'image cachée et la sauvegarder
void reconstruireImageCachee(const std::vector<int>& lsbValues) 
{
 
    const std::string& cheminImageCachee; //  son chemin d'acces pour aller le stocker quand on va finir de l'extraire
    const std::string& cheminImageHote; // ici on veut son chemin d'acces pour avoir les dimensions de l'image hote
    // Étape 1 : Vérifier que les LSB ne sont pas vides
    if (lsbValues.empty()) {
        std::cerr << "Erreur : Le tableau des LSB est vide." << std::endl;
        return;
    }

    // Étape 2 : Charger l'image hôte pour obtenir ses dimensions
    cv::Mat imageHote = cv::imread(cheminImageHote);
    if (imageHote.empty()) {
        std::cerr << "Erreur : Impossible de charger l'image hôte." << std::endl;
        return;
    }

    // Récupérer les dimensions de l'image hôte
    int largeur = imageHote.cols;  // Largeur de l'image
    int hauteur = imageHote.rows;  // Hauteur de l'image

    // Étape 3 : Vérifier que la taille des LSB correspond aux dimensions de l'image hôte
    if (lsbValues.size() != largeur * hauteur) {
        std::cerr << "Erreur : La taille des LSB ne correspond pas aux dimensions de l'image hôte." << std::endl;
        return;
    }

    // Étape 4 : Créer une image binaire (grayscale, 1 canal)
    cv::Mat imageCachee(hauteur, largeur, CV_8UC1); // Image en niveaux de gris (1 canal)
    for (int i = 0; i < lsbValues.size(); i++) {
        int row = i / largeur; // Calculer la ligne
        int col = i % largeur; // Calculer la colonne
        imageCachee.at<uchar>(row, col) = lsbValues[i] * 255; // Convertir 0/1 en intensité 0/255
    }

    // Étape 5 : Sauvegarder l'image reconstruite
    if (cv::imwrite(cheminImageCachee, imageCachee)) {
        std::cout << "Image cachée extraite et sauvegardée avec succès dans : " << cheminImageCachee << std::endl;
    } else {
        std::cerr << "Erreur : Impossible de sauvegarder l'image à l'emplacement spécifié." << std::endl;
    }
}




