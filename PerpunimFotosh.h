//
//  ToneNgjyrash.h
//  Projekt Endi Zhupani IE206 Image Processing
//
//

#ifndef __Projekt_Endi_Zhupani_IE206_Image_Processing__ToneNgjyrash__
#define __Projekt_Endi_Zhupani_IE206_Image_Processing__ToneNgjyrash__

#include <stdio.h>

#endif /* defined(__Projekt_Endi_Zhupani_IE206_Image_Processing__ToneNgjyrash__) */

#include <cv.h>
#include <highgui.h>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv; // namespace ku gjendet te gjitha komandat e openCV

class ToneNgjyrash {
public:
    /*Merr si argument nje matrice Mat dhe emrin e dritares. 
     i jep pixelave tonin sepia dhe e shfaq ne dritaren e specifikuar
     */
    void sepia(Mat&, string);
    /*merr si argument nje matrice Mat dhe e kthen ne sepia
     */
    void sepiaPerVideo(Mat&);
    /* merr si argument nje matrice Mat dhe kthen versionin IplImage te saj*/
    //IplImage*konverto (const Mat);
    //mban foton origjinale
    Mat fotoOrigjinale;
};
class Efekte {
public:
    void Contrast_Brightenes(Mat&,string);
    void Sharpen (Mat&);
    void Blur_Or_Smooth (Mat&, string);
    void goBack( Mat&);
    Mat fotoOrigjinale;
};
class Editim {
public:
    void rotullo(Mat&, string);
    Mat fotoOrigjinale;
};
