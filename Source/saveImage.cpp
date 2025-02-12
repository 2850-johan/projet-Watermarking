#include "saveImage.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <filesystem>

using namespace std;

void sauvegarderImage(cv::Mat& image, string& repertoire, string& nomFichier) {
    if (image.empty()) {
        cerr << "Erreur : L'image est vide ou non valide." << endl;
        return;
    }

    // Vérifier si le répertoire existe, sinon le créer
    if (!filesystem::exists(repertoire)) {
        cout << "Le répertoire n'existe pas. Création en cours..." << endl;
        if (!filesystem::create_directories(repertoire)) {
            cerr << "Erreur : Impossible de créer le répertoire." << endl;
            return;
        }
    }

    // Construire le chemin complet du fichier
    string cheminComplet = repertoire + "/" + nomFichier;

    // Enregistrer l'image dans le répertoire spécifié
    if (cv::imwrite(cheminComplet, image)) {
        // Vérifier si le fichier existe après l'enregistrement
        if (filesystem::exists(cheminComplet)) {
            cout << "Image enregistrée avec succès dans : " << cheminComplet << endl;
        } else {
            cerr << "Erreur : L'image n'a pas été trouvée dans le répertoire après la sauvegarde." << endl;
        }
    } else {
        cerr << "Erreur : Impossible d'enregistrer l'image." << endl;
    }
}
