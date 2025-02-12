#include "Reconstructimage.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>


cv::Mat reconstruireImage(const std::vector<int>& pixelValues, int width, int height) {
    // Étape 1 : Validation de la taille du tableau
    if (pixelValues.size() != width * height * 3) {
        std::cerr << "Erreur : Taille invalide du tableau de pixels. "
                  << "Attendu : " << width * height * 3 
                  << ", Reçu : " << pixelValues.size() << std::endl;
        return cv::Mat();
    }

    // Étape 2 : Validation des valeurs des pixels
    for (size_t i = 0; i < pixelValues.size(); i++) {
        if (pixelValues[i] < 0 || pixelValues[i] > 255) {
            std::cerr << "Erreur : Valeur de pixel invalide à l'indice " 
                      << i << ": " << pixelValues[i] << std::endl;
            return cv::Mat();
        }
    }

    // Étape 3 : Transformation en matrice colonne unique
    cv::Mat colonneUnique(static_cast<int>(pixelValues.size()), 1, CV_8UC1);
    for (size_t i = 0; i < pixelValues.size(); i++) {
        colonneUnique.at<uchar>(i, 0) = static_cast<uchar>(pixelValues[i]);
    }

    // Étape 4 : Extraction des canaux (Bleu, Vert, Rouge)
    int totalPixels = width * height;
    cv::Mat blueColumn = colonneUnique.rowRange(0, totalPixels);
    cv::Mat greenColumn = colonneUnique.rowRange(totalPixels, 2 * totalPixels);
    cv::Mat redColumn = colonneUnique.rowRange(2 * totalPixels, 3 * totalPixels);

    // Étape 5 : Reshape des canaux en fonction des dimensions de l'image
    cv::Mat blueChannel = blueColumn.reshape(1, height);
    cv::Mat greenChannel = greenColumn.reshape(1, height);
    cv::Mat redChannel = redColumn.reshape(1, height);

    // Étape 6 : Fusion des canaux en une image
    std::vector<cv::Mat> channels = {blueChannel, greenChannel, redChannel};
    cv::Mat reconstitutedImage;
    cv::merge(channels, reconstitutedImage);

    // Étape 7 : Affichage des dimensions pour contrôle
    std::cout << "Dimensions de l'image reconstruite : " 
              << reconstitutedImage.cols << " x " 
              << reconstitutedImage.rows << std::endl;

    return reconstitutedImage;
}
