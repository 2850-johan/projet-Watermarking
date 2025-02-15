#include "Audiotodec.h"

   #include <vector>
   #include <fstream>
   #include <iostream>

   std::vector<int> extraireDecimalValuesAudio(const std::string& cheminFichier) {
       std::vector<int> DecimalAudioValues;
       std::ifstream fichier(cheminFichier, std::ios::binary);
       if (!fichier.is_open()) {
           std::cerr << "Erreur : Impossible d'ouvrir le fichier audio : " << cheminFichier << std::endl;
           return DecimalAudioValues;
       }

       char octet;
       while (fichier.read(&octet, sizeof(char))) {
           DecimalAudioValues.push_back(static_cast<unsigned char>(octet));
       }

       fichier.close();
       return DecimalAudioValues;
   }
















    