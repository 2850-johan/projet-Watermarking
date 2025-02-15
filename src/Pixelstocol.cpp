#include "Pixelstocol.h"
#include <opencv2/opencv.hpp>  
#include <iostream>            
#include <vector>              


std::vector<int> extrairePixelValues(const std::string& cheminImage) {
    // Charger l'image couleur d'origine
    cv::Mat image = cv::imread(cheminImage); 
    if (image.empty()) {  
        std::cerr << "Erreur : Impossible de charger l'image." << std::endl;
        return {};        // Si l'image ne peut être chargée, renvoyer un tableau vide
    }

    // Diviser l'image en trois canaux (B, G, R)
    std::vector<cv::Mat> channels;  
    cv::split(image, channels);     

    // Vérifier que l'image a bien trois canaux
    if (channels.size() != 3) {
        std::cerr << "Erreur : L'image n'est pas au format BGR." << std::endl;
        return {}; 
    }

    // Transformer chaque canal en une seule colonne
    cv::Mat blue_column = channels[0].reshape(1, channels[0].rows * channels[0].cols);
    cv::Mat green_column = channels[1].reshape(1, channels[1].rows * channels[1].cols);
    cv::Mat red_column = channels[2].reshape(1, channels[2].rows * channels[2].cols);

    // Combiner les trois colonnes en une seule
    cv::Mat colonneUnique;
    cv::vconcat(blue_column, green_column, colonneUnique);  
    cv::vconcat(colonneUnique, red_column, colonneUnique);  

    // Stocker les valeurs de colonneUnique dans un std::vector<int>
    std::vector<int> pixelValues(colonneUnique.rows);
    for (int i = 0; i < colonneUnique.rows; i++) {
        pixelValues[i] = colonneUnique.at<uchar>(i, 0);  
    }

    return pixelValues; 
};