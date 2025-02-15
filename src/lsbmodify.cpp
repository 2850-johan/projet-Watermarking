#include "lsbmodify.h"
#include <opencv2/opencv.hpp>


#include <iostream>

using namespace std;
using namespace cv;





Mat  lsbreplace(Mat& imagehideuc ,Mat&imagehidein) {


//Cibler la dernière colonne,la colonne des lsb de l'image hôte
Mat lsbcol=imagehidein.col(imagehidein.cols-1);


//Créer une matrice qui servira pour le stockage de la dernière colonne de l'image 
Mat matricelsb=Mat::zeros(lsbcol.rows,1,CV_8UC1);


//Cette boucle permet en fait d'insérer les valeurs de la colonne unique des lsb dans la matricelsb
for (int i=0;i<lsbcol.rows;i++) {
	uchar valeur=lsbcol.at<uchar>(i,0);
	matricelsb.at<uchar>(i,0)=valeur ; 



};

//Ici on vérifie si le nombre de lignes de la matrice à colonne
//unique de l'image à cacher est supérieur ou pas à celle de matricelsb
//Si oui on effectue le remplacement de la partie correspondante à la taille de 
//imagehideuc dans matricels
 if (imagehideuc.rows > matricelsb.rows) {
        cout << "Erreur : La colonne unique de l'image à cacher est trop grande pour remplacer une portion de la matrice LSB." << endl;
       return Mat();
    }
else {


           for (int i=0;i<imagehideuc.rows;++i) {

 		matricelsb.at<uchar>(i,0)=imagehideuc.at<uchar>(i,0) ;


 	};

} ;	
// Remplacement de la colonne des lsb de l'image hôte par matricelsb qui contient l'image cachée



 if (imagehidein.rows == matricelsb.rows)


 {
 	
 	matricelsb.copyTo(imagehidein.col(imagehidein.cols - 1));

 } else {
	cout<<"Les matrices n\'ont pas le même nombre de ligne"<<endl;
};


return imagehidein;
};


/*





int main() {
// Étape 1 : Extraction des valeurs de l'image à cacher
vector<int> imhide = extrairePixelValues("/home/nel/Watermark/Images/titre.jpeg");

// Étape 2 : Conversion du vecteur en binaire
vector<vector<int>> binaryval = decimalToBinary(imhide);

// Étape 3 : Conversion en matrice
Mat binaryMatHide = Mat(binaryval.size(), binaryval[0].size(), CV_32S);
for (int i = 0; i < binaryval.size(); ++i) {
    for (int j = 0; j < binaryval[i].size(); ++j) {
        binaryMatHide.at<int>(i, j) = binaryval[i][j];
    }
}

// Étape 4 : Transformation en colonne unique
Mat uniqueColumn = bintocol(binaryMatHide);

// Étape 5 : Extraction des valeurs de l'image hôte
vector<int> imhote = extrairePixelValues("/home/nel/Watermark/Images/top-section-bg.jpeg");

// Étape 6 : Conversion en binaire et matrice
vector<vector<int>> binvalhote = decimalToBinary(imhote);
Mat binaryMatHote = Mat(binvalhote.size(), binvalhote[0].size(), CV_32S);
for (int i = 0; i < binvalhote.size(); ++i) {
    for (int j = 0; j < binvalhote[i].size(); ++j) {
        binaryMatHote.at<int>(i, j) = binvalhote[i][j];
    }
}

// Étape 7 : Remplacement des bits LSB
Mat modifiedBitsValues = lsbreplace(uniqueColumn, binaryMatHote);

// Étape 8 : Vérification des LSB
cout << "=== Vérification des LSB ===" << endl;
Mat lsbCol = modifiedBitsValues.col(modifiedBitsValues.cols - 1).clone();

// Extraire la partie correspondant à la taille de uniqueColumn
Mat extractedPart = lsbCol.rowRange(0, uniqueColumn.rows).clone();


cout<<"Valeurs cachées "<<endl;
    for (int i = 0 ; i < min(10,extractedPart.rows); ++i) {

        cout <<(int)extractedPart.at<uchar>(i,0) <<" "<<endl;}


// Comparer les matrices
bool isIdentical = (cv::countNonZero(extractedPart != uniqueColumn) == 0);

if (isIdentical) {
    cout << "La colonne unique a bien été insérée dans la dernière colonne des LSB." << endl;
} else {
    cout << "Erreur : Les valeurs insérées ne correspondent pas à la colonne unique." << endl;
}

}
*/