#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Fonction pour extraire un bit d'un octet
bool getBit(unsigned char byte, int position) {
    return (byte >> position) & 1;
}

// Fonction pour extraire un texte d'une image
string extractTextFromImage(const string &imagePath) {
    ifstream inputFile(imagePath, ios::binary);
    if (!inputFile) {
        cerr << "Erreur lors de l'ouverture du fichier." << endl;
        return "";
    }

    inputFile.seekg(54); // Saute le header BMP
    vector<unsigned char> pixelData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    string extractedText;
    char currentChar = 0;
    int bitCount = 0;

    for (size_t i = 0; i < pixelData.size(); ++i) {
        bool bit = getBit(pixelData[i], 0);
        currentChar = (currentChar << 1) | bit;

        bitCount++;
        if (bitCount == 8) {
            if (currentChar == '|') break; // Délimiteur trouvé
            extractedText += currentChar;
            currentChar = 0;
            bitCount = 0;
        }
    }

    size_t textSize = stoi(extractedText); // Taille du texte
    extractedText.clear();
    currentChar = 0;
    bitCount = 0;

    for (size_t i = 0; i < pixelData.size(); ++i) {
        bool bit = getBit(pixelData[i], 0);
        currentChar = (currentChar << 1) | bit;

        bitCount++;
        if (bitCount == 8) {
            extractedText += currentChar;
            currentChar = 0;
            bitCount = 0;

            if (extractedText.size() == textSize) break;
        }
    }

    return extractedText;
}

int main() {
    string imagePath;
    cout << "Entrez le chemin de l'image contenant le texte caché : ";
    cin >> imagePath;

    string extractedText = extractTextFromImage(imagePath);
    cout << "Texte extrait : " << extractedText << endl;

    return 0;
}
