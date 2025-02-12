#include <opencv2/opencv.hpp> 
#include <iostream>
using namespace cv;
using namespace std;


Mat  extract(Mat& imagehideuc ,Mat&imagehidein) {


//Cibler la dernière colonne,la colonne des lsb de l'image hôte
Mat lsbcol=imagehidein.col(imagehidein.cols-1);
int hidenheight=imagehideuc.rows*imagehideuc.cols;
Mat hidenbytes=lsbcol.rowRange(0,hidenheight);


if (hidenheight > lsbcol.rows){

	cerr<<"L'image n'est pas cachée dans l'image hôte";
	return -1;
};



return hidenbytes;



}



