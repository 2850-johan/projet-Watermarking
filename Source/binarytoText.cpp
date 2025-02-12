#include "binarytoText.h"

#include <bitset>
#include<string>
#include <filesystem>
#include <vector>


#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>


using namespace std;
using namespace cv;
//using namespace std::filesystem;



string binaryToText(const string& binaryString) {
    // Vérifier si la longueur de la chaîne binaire est un multiple de 8
    if (binaryString.size() % 8 != 0) {
        cerr << "Erreur : La longueur de la chaîne binaire n'est pas un multiple de 8." << endl;
        return "";
    }

    string message = ""; // Le message reconstruit

    for (size_t i = 0; i < binaryString.size(); i += 8) {
        // Extraire 8 bits de la chaîne
        string byte = binaryString.substr(i, 8);

        // Convertir les 8 bits en un entier décimal
        char character = static_cast<char>(bitset<8>(byte).to_ulong());

        // Ajouter le caractère au message
        message += character;
    }

    return message;
}




