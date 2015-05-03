//
//  KomunikimMeUser.h
//  Projekt Endi Zhupani IE206 Image Processing
//Header per file-n me klasat te cilat shfaqin menute e ndryshme nga te cilat useri mund te zgjedhe veprime.

#ifndef __Projekt_Endi_Zhupani_IE206_Image_Processing__KomunikimMeUser__
#define __Projekt_Endi_Zhupani_IE206_Image_Processing__KomunikimMeUser__

#include <stdio.h>
#include <iostream>
#include <iomanip>
using namespace std;

class Menu
{
public:
    void menuFoto(); // shfaq menune e veprimeve me fotot
    int zgjedhjaVideo(); // shfaq menune per te zgjedhur webcam ose video nga sistemi dhe kthen zgjedhjen
    void menuVideo();// shfaq menune e veprimeve me video
};
#endif /* defined(__Projekt_Endi_Zhupani_IE206_Image_Processing__KomunikimMeUser__) */
