#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <iostream>
#include "/home/nel/Watermark/tests/naomie.cpp"
#include "/home/nel/Watermark/tests/extractionLSB.cpp"
#include "/home/nel/Watermark/tests/reconstructionImage.cpp"

int main() {
    // Charger les valeurs des pixels et extraire les LSB
    std::string cheminImage = "image_entree.png";
    std::vector<int> pixelValues = extrairePixelValues(cheminImage);
    std::vector<int> lsbValues = extraireLSBDepuisTableau(pixelValues);

    // Chemin de l'image hôte pour obtenir ses dimensions
    std::string cheminImageHote = "image_entree.png";

    // Reconstruire et sauvegarder l'image cachée
    reconstruireImageCachee(lsbValues);

    return 0;
}