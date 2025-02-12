
📌 Projet Watermarking
Description
Ce projet permet d'effectuer plusieurs actions à l'aide de la méthode LSB (Least Significant Bit) :
 1️⃣ Cacher une image dans une image.
 2️⃣ Cacher un audio dans une image.
 3️⃣ Extraire une image ou un audio d'une image précise.
🎯 Objectif
L'objectif de ce projet est de développer un système utilisant la méthode LSB pour intégrer et extraire des données (image/audio) dans une image.
🛠️ Prérequis (Ubuntu)
Avant d'exécuter ce projet, assurez-vous d'avoir :
 ✅ Un éditeur de texte de votre choix (Sublime Text, VS Code, etc.).
 ✅ La bibliothèque OpenCV installée.
 ✅ Les dépendances nécessaires pour le langage C++.
Installation d'OpenCV sur Ubuntu :
sudo apt update
sudo apt install libopencv-dev

📥 Installation
Suivez ces étapes pour cloner et configurer le projet :
1️⃣ Cloner le projet depuis GitHub :
git clone https://github.com/2850-johan/projet-Watermarking.git

2️⃣ Explorer l'arborescence du projet :
 Le projet est structuré en trois branches :
main : Branche principale contenant le code final.
dev : Branche de développement.
dec2bin : Branche dédiée à la conversion décimale-binaire.
🚀 Exécution
1️⃣ Se positionner sur la branche main :
git checkout main

2️⃣ Vérifier la structure du projet :
cd projet-Watermarking
ls

Vous devriez voir les dossiers suivants :
Images/ : Contient les fichiers d'exemple.
Sources/ : Contient les fichiers de test.
Include/ : Toutes les entêtes de fonctions principales du projet.
makefile : Permettant d'exécuter le programme
3️⃣ Modifier les chemins d'accès dans le code si nécessaire (/home/user/...) pour s'assurer du bon fonctionnement.
4️⃣ Compiler et exécuter le programme :
make

📝 Remarque
Si vous rencontrez des erreurs lors de l'exécution, vérifiez que toutes les bibliothèques et dépendances sont bien installées.

