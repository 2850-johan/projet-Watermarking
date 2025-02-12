#include <iostream>            

#include <vector>              
using namespace std;









vector<unsigned char> bitsToDecimal(const vector<int>& bits) {
    vector<unsigned char> decimalValues;  // Stocke les octets extraits
    unsigned char currentByte = 0;  // Variable pour composer un octet
    int bitCount = 0;  // Compte les bits ajoutés à l'octet actuel

    // Parcourt chaque bit
    for (int bit : bits) {
        currentByte = (currentByte << 1) | bit;  // Ajoute le bit à l'octet
        bitCount++;

        // Si on a 8 bits, on forme un octet complet
        if (bitCount == 8) {
            decimalValues.push_back(currentByte);  // Ajoute l'octet au vecteur
            currentByte = 0;  // Réinitialise pour le prochain octet
            bitCount = 0;
        }
    }
    return decimalValues;  // Retourne les octets extraits
}