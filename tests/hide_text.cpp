#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Fonction pour insérer un bit dans un octet
void setBit(unsigned char &byte, int position, bool bit) {
    if (bit)
        byte |= (1 << position); // Met le bit à 1
    else
        byte &= ~(1 << position); // Met le bit à 0
}

// Fonction pour cacher un texte dans une image
void hideTextInImage(const string &imagePath, const string &outputPath, const string &text) {
    ifstream inputFile(imagePath, ios::binary);
    ofstream outputFile(outputPath, ios::binary);

    if (!inputFile || !outputFile) {
        cerr << "Erreur lors de l'ouverture des fichiers." << endl;
        return;
    }

    vector<unsigned char> header(54); // Lire le header BMP
    inputFile.read(reinterpret_cast<char *>(header.data()), header.size());
    outputFile.write(reinterpret_cast<char *>(header.data()), header.size());

    vector<unsigned char> pixelData((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());

    string dataToHide = to_string(text.size()) + "|" + text; // Taille + texte
    size_t textIndex = 0;

    for (size_t i = 0; i < pixelData.size() && textIndex < dataToHide.size(); ++i) {
        char currentChar = dataToHide[textIndex];
        bool bit = (currentChar >> (7 - (i % 8))) & 1;
        setBit(pixelData[i], 0, bit); // Modifier le bit LSB

        if (i % 8 == 7) textIndex++;
    }

    if (textIndex < dataToHide.size()) {
        cerr << "L'image est trop petite pour contenir le texte." << endl;
        return;
    }

    outputFile.write(reinterpret_cast<char *>(pixelData.data()), pixelData.size());
    cout << "Texte caché avec succès dans " << outputPath << endl;
}

int main() {
    string imagePath, outputPath, text;
    cout << " Entrez le chemin de l'image source (JPEG) : ";
    cin >> imagePath;
    cout << "Entrez le chemin de l'image de sortie : ";
    cin >> outputPath;
    cout << "Entrez le texte à cacher : ";
    cin.ignore();
    getline(cin, text);

    hideTextInImage(imagePath, outputPath, text);
    return 0;
}
