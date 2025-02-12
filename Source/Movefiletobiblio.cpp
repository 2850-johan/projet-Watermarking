#include "Movefiletobiblio.h"
#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
using namespace std::filesystem;

// Fonction pour déplacer un fichier vers un répertoire qui nous sert de bibliothèque de données

void deplacerFichier(const string& cheminSource, const string& repertoireCible) {
    path source(cheminSource);
    path cible(repertoireCible);

    // Vérifier si le fichier source existe
    if (!exists(source) || !is_regular_file(source)) {
        cerr << "Erreur : Le fichier source n'existe pas ou n'est pas valide." << endl;
        return;
    }

    // Vérifier si le répertoire cible existe, sinon le créer
    if (!exists(cible)) {
        create_directories(cible);
    }

    // Construire le chemin final dans le répertoire cible
    path cheminFinal = cible / source.filename();

    // Déplacer le fichier
    try {
        rename(source, cheminFinal);
        cout << "Fichier déplacé avec succès dans : " << cheminFinal << endl;
    } catch (const filesystem_error& e) {
        cerr << "Erreur lors du déplacement du fichier : " << e.what() << endl;
    }
}
