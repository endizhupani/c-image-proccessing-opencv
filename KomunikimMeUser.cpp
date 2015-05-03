//
//  KomunikimMeUser.cpp
//  Projekt Endi Zhupani IE206 Image Processing
//
//  Created by Endi Zhupani on 28/01/15.
//  Copyright (c) 2015 Endi Zhupani. All rights reserved.
//
#include <highgui.h>
#include "KomunikimMeUser.h"
using namespace cv;

void Menu:: menuFoto()
{
    string veprimi [] = {"","Ngjyra: Sepia", "Ngjyra: Bardhe e zi", "Efekt: Negativ" , "Efekt: Blur", "Efekt: Sharpen", "Efekt: Contrast & Brightenes","Back","Rotate", "Mbyll Foton"};
    cout << "Butoni" << setw(5) << " "<< "Veprimi" <<endl;
    for (int i = 1; i<10; i++){
        if (i == 5)
        {
            cout << setw(6) << "'s'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        else if (i == 6)
        {
            cout << setw(6) << "'c'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        else if (i == 7)
        {
            cout << setw(6) << "'b'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        else if (i == 8)
        {
            cout << setw(6) << "'r'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        else if (i == 9)
        {
            cout << setw(6) << "ESC" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        cout << setw(6) << i << setw(5) << " " << veprimi [i] << endl;
    };
}
int Menu:: zgjedhjaVideo()
{
    int zgjedhja;
    string veprimi [] = {"","Hap webcam", "Hap video nga sistemi"};
    cout << "Butoni" << setw(5) << " "<< "Veprimi" <<endl;
    for (int i = 1; i<3; i++){
        cout << setw(6) << i << setw(5) << " " << veprimi [i] << endl;
    };
    namedWindow("zgjidh");
    while (true){
        zgjedhja = waitKey();
        bool zSakte = false;
        if (zgjedhja>=49 && zgjedhja<51) // zgjedh 1 ose 2
            zSakte = true;
        if (zSakte)
            break;
        cout << "Ju lutem zgjidhni nje numer qe perfshihet ne Menu. ";
    }
    destroyWindow("zgjidh");
    return zgjedhja;
}
void Menu:: menuVideo()
{
    string veprimi [] = {"","Ngjyra: Sepia", "Ngjyra: Bardhe e zi", "Efekt: Negativ" , "Back", "Mbyll videon", "Play/Pause (Jo per webcam)"};
    cout << "Butoni" << setw(5) << " "<< "Veprimi" <<endl;
    for (int i = 1; i<7; i++){
        if (i ==4 )
        {
            cout << setw(6) << "'b'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        else if (i == 5)
        {
            cout << setw(6) << "'ESC'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        else if (i == 6)
        {
            cout << setw(6) << "'p'" << setw(5) << " " << veprimi [i] << endl;
            continue;
        }
        cout << setw(6) << i << setw(5) << " " << veprimi [i] << endl;
    };
}
