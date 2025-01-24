#include <opencv2/opencv.hpp>
#include "/home/nel/Watermark/tests/naomie.cpp"


#include <iostream>

using namespace std;
using namespace cv;

std::vector<int> extraireLSB(const std::vector<int>& pixelValues) {
    //Etape 1 :  Vérifier que le tableau n'est pas vide
    if (pixelValues.empty()) {
        std::cerr << "Erreur : Le tableau des pixels est vide." << std::endl;
        return {}; // Retourner un tableau vide en cas d'erreur
    }

    // Etape 2 : Initialisation du vecteur pour stocker les LSB
    std::vector<int> lsbValues;

    // Parcourir chaque valeur du tableau
    for (const auto& pixelValue : pixelValues) {
        // Extraire le LSB (dernier bit) avec une opération bit à bit
       // Si le dernier bit (LSB) de pixelValue est 1, alors le résultat sera 1.
        //Si le dernier bit (LSB) de pixelValue est 0, alors le résultat sera 0.
        int lsb = pixelValue & 1; // Effectuer un "AND" avec 1 pour obtenir le LSB
        lsbValues.push_back(lsb); // Ajouter le LSB au vecteur
    }

    return lsbValues; // Retourner les valeurs des LSB
}


/*std::string cheminImage = "chemin/vers/image.png";
std::vector<int> lsbValues = extraireLSB(cheminImage);

if (!lsbValues.empty()) {
    std::cout << "Extraction des LSB réussie !" << std::endl;
    // Afficher les premiers LSB (par exemple, les 20 premiers bits)
    for (size_t i = 0; i < 20 && i < lsbValues.size(); i++) {
        std::cout << lsbValues[i] << " ";
    }
    std::cout << std::endl;
} else {
    std::cerr << "Erreur lors de l'extraction des LSB." << std::endl;
}
