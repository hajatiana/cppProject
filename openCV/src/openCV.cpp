//============================================================================
// Name        : openCV.cpp
// Author      : Hajatiana
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

using namespace std;
using namespace cv;

void traitementLumiere();
void changeLumiere(int, void*);
void changeContraste(int, void*);
void filtreImage(int, void*);

Mat src, dest, kern;
int lumiere_size=50;
int lumiere_max=100;
int contraste_size=50;
int contraste_max=100;
int width=800;
int height=600;

int main() {
	src = imread("images/grenoble.jpg", IMREAD_UNCHANGED);
	kern = (Mat_<char>(3,3) << 0, -1, 0,-1, 5, -1, 0, -1, 0);

	namedWindow("OpenCV",CV_WINDOW_AUTOSIZE);
	resizeWindow("OpenCV", width, height);
	moveWindow("OpenCV", 100, 0);

	traitementLumiere();
	waitKey(0);
	destroyAllWindows();
	return 0;
}

void traitementLumiere(){
	imshow("OpenCV",src);
	string name = "Normalisation ";
	char* nameb1 = "button1";
	createTrackbar( "Lumière   ", "OpenCV", &lumiere_size, lumiere_max, changeLumiere);
	createTrackbar( "Contraste ", "OpenCV", &contraste_size, contraste_max, changeContraste);
	createButton(name.c_str(),filtreImage,nameb1, CV_CHECKBOX,1);
}

void changeLumiere(int, void*){
	int l=(lumiere_size-50)*510/100;
	dest = src + Scalar(l, l, l);
	imshow( "OpenCV", dest);
}

void changeContraste(int, void*){
	double l= (double) (contraste_size-50)/50+1;
	src.convertTo(dest, -1, l, 0);
	imshow( "OpenCV", dest);
}

void filtreImage(int, void*){
	filter2D(src,dest,src.depth(),kern);
}
