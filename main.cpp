//
//  main.cpp
//  Projekt Endi Zhupani IE206 Image Processing
//
//  Created by Endi Zhupani on 19/01/15.
//  Copyright (c) 2015 Endi Zhupani. All rights reserved.
/*
 Program qe manipulon foto ose video duke kryer mbi to veprime baze si shtime filtrash shtime efektesh 
 ose editime. Per editimin e imazheve perdor librarite e OpenCV 2.4.10
 */
#include <opencv2/core/core.hpp>
#include <string>
#include "PerpunimFotosh.h"
#include "KomunikimMeUser.h"
using namespace cv;
using namespace std;
int sliderPoz = 0; //pozicioni i sliderit ne trackbarin e Pozicionit te Videos tek ngarkimi i videos nga sistemi
//objekti qe do te ngarkoje videon nga sistemi
VideoCapture cap;
void leviziSlideri(int,void*)
{
    cap.set(CV_CAP_PROP_POS_FRAMES, sliderPoz*100);
}
//VideoCapture cap;//vendos filepath te plote
//me levizjen e silderit updateohet edhe pozicioni i videos sipas vleres se sliderit

int main( int argc, char* argv[])
{
    cout << "Projekti C++, Image Processing Endi Zhupani IE206" <<endl;
    cout << "Shtypni 1 per te filluar ekzekutimin ose -1 per te dale nga programi. " ;
    int ekzekutimi;
    cin >> ekzekutimi;
    int f_v; // hap foto apo video
    int llojiIVideos;// nga sistemi apo webcam
    int zgjedhjaPerdoruesit = -1;
    Menu shfaqMenu; //objekt qe shfaq menute e ndryshme
    ToneNgjyrash shtoTon; //objekt qe shton tone ngjyrash
    Efekte shtoEfekt;
    Editim edit;
    while (ekzekutimi != -1) // user do te vazhdoje ekzekutimin
    {   //shfaqet menuja kryesore
        cout << "MENU" <<endl;
        cout << "Butoni"<<setw(5) << " "<< "Veprimi" << endl;
        cout << setw(6) << "1" << setw(5) << " " << "Load Foto" <<endl;
        cout << setw(6) << "2" << setw(5) <<  " " <<"Load Video" <<endl;
        namedWindow("Zgjidh"); //per te perdorur waitKey()
        f_v = waitKey(0); // pret shtypjen e nje butoni
        destroyWindow("Zgjidh");
        while (true){ // mbaron kur mbaron switch
        switch (f_v){
            case 50: // shtyp '2' -> zgjedh video
                llojiIVideos= shfaqMenu.zgjedhjaVideo();//zgjedh nga do ta hapi videon
                if (llojiIVideos==49){//shtyp '1' -> zgjedh webcam
                VideoCapture cap(0);
                if (!cap.isOpened()){ //behet kontrolli a eshte hapur
                    cout << "Ngarkimi nuk u krye me sukses. Programi po mbyllet" << endl;
                    return -1;
                }
                    else cout << "Ngarkimi u krye me sukses" <<endl;
                    shfaqMenu.menuVideo(); //shfaqet menuja qe jep veprimet qe kryhen + butonat
                    namedWindow("VideoDemo", CV_WINDOW_NORMAL);//dritarja grafike
                    int vleraSliderBrightenes = 25; //vlera fillestare ne slider
                    int vleraSliderContrast = 25;
                    //krijohen trackbaret me vlere nga 0 - 50
                    createTrackbar("Brightenes", "VideoDemo", &vleraSliderBrightenes, 50);
                    createTrackbar("Contrast", "VideoDemo", &vleraSliderContrast, 50);
                    while (1)//fillohet cikli qe do shfaqe 1 pas nje te gjitha frameqe lexohen nga video
                    {
                        Mat frame;
                        Mat *framePtr = &frame;
                        bool uLexua = cap.read(frame); // lexohet frame e rradhes ne video
                        if (!uLexua) // lexim i suksesshem apo jo
                        {
                            cout <<"Nuk u lexua dot frame. Programi po mbyllet!" << endl;
                            return -1;
                        }
                        resize(*framePtr,*framePtr,Size(512,412), CV_INTER_AREA);//INTER_AREA per te patur kualitet te mire
                        if (zgjedhjaPerdoruesit == 49) // shtyp '1'
                        {
                            shtoTon.sepiaPerVideo(frame);
                        }
                        else if (zgjedhjaPerdoruesit == 50) //shtyp '2'
                        {
                            cvtColor(frame, frame, CV_BGR2GRAY); //converton nga BGR (Blue Green Red) ne Bardhe e zi
                        }
                        else if (zgjedhjaPerdoruesit == 51) // kerkon invertim ngjyrash
                        {
                            bitwise_not(frame, frame);
                        }
                        //do te jape ndryshimin e brightenes merr vlera nga -250 - 250
                        int ndryshimiBrightenes = vleraSliderBrightenes*10-250;
                        //do jape ndryshimin e contrast. merr vlera 0 - 2
                        double ndryshimiContrast = vleraSliderContrast*10/250.0;
                        // behet convertimi i imazhit sipas brightenesit dhe contrastit qe kerkohet
                        //nqs sliderat ne trackbar skane ndryshuar imazhi mbetet sic eshte.
                        frame.convertTo(frame,-1,ndryshimiContrast,ndryshimiBrightenes);
                        int tastIShtypur = waitKey(10); //i jepet perdoruesit kohe per te shtypur buton
                        imshow("VideoDemo", frame);
                        if (tastIShtypur == 112) //shtyp 'p'
                            waitKey(0); // ngecet ekzekutimi deri sa te shtypi buton tjeter
                        else if (tastIShtypur == 49) zgjedhjaPerdoruesit = tastIShtypur; // shtyp 1
                        else if (tastIShtypur == 50) zgjedhjaPerdoruesit = tastIShtypur; // 2
                        else if (tastIShtypur == 51) zgjedhjaPerdoruesit = tastIShtypur;// 3
                        // shtypet b. zgjedhja perdoruesit merr vleren 98 dhe shfaqen frame origjinale
                        // keshtu krijohet veprimi back.
                        else if (tastIShtypur == 98)
                        {
                            zgjedhjaPerdoruesit = tastIShtypur;
                            setTrackbarPos("Brightenes", "VideoDemo", 25);
                            setTrackbarPos("Contrast", "VideoDemo", 25);
                            vleraSliderBrightenes = 25;
                            vleraSliderContrast = 25;
                        }
                        else if (tastIShtypur == 27) //shtyp ESC
                        {
                            cout << "Dritarja po mbyllet"<< endl;
                            break;
                        }
                    }
                    destroyAllWindows();
                }
                if (llojiIVideos == 50){ // zgjedh te hape video nga sistemi
                    /*Funksionon njelloj si video nga webcam me perjashtim te shtimit te nje 
                     treckbari qe mban pozicionin e videos me te cilin video mund te levizet para 
                     ose mbrapa.
                     */
                    destroyAllWindows();
                    cout << "Ju lutem jepni filepath te PLOTE te file qe doni te hapni." <<endl;
                    string filepath;
                    cin.ignore(); //behet flush console sepse mund te kete karaktere '/n' te cilat perfundojne funksionin getline pa e marre inputin.
                    getline(cin, filepath);
                    cap.open(filepath);
                    if (!cap.isOpened()){
                        cout << "Ngarkimi nuk u krye me sukses. Programi po mbyllet" << endl;
                        return -1;
                    }
                    else cout << "Ngarkimi u krye me sukses" <<endl;
                    shfaqMenu.menuVideo();
                    namedWindow("VideoDemo", CV_WINDOW_NORMAL);
                    int vleraSliderBrightenes = 25; //vlera fillestare ne slider
                    int vleraSliderContrast = 25;
                    int NumriFrames = cap.get(CV_CAP_PROP_FRAME_COUNT); //merret numri i frames
                    int framesTekaluara = 0;//sa frames jane shfaqur
                    //krijohet trackbari pozicioni i cili updateon poziv=cionin e videos sa her leviz slideri
                    createTrackbar("Pozicioni", "VideoDemo", &sliderPoz, NumriFrames/100,leviziSlideri);
                    createTrackbar("Brightenes", "VideoDemo", &vleraSliderBrightenes, 50);
                    createTrackbar("Contrast", "VideoDemo", &vleraSliderContrast, 50);
                    while (1)
                    {
                        Mat frame;
                        Mat *framePtr = &frame;
                        if (framesTekaluara>=NumriFrames) // arrihet ne fund te videos
                        {
                            cout << "Video mbaroi. Shtypni 'p' per ta filluar edhe nje here ose cdo buton tjeter per te vazhduar" << endl;
                            int vazhdo = waitKey(0);
                            if (vazhdo == 112)
                                cap.set(CV_CAP_PROP_POS_FRAMES,1);
                            else //nqs nuk zgjedh te vazhdoje dil nga cikli i shfaqjes se frameve
                            break;
                        }
                        bool uLexua = cap.read(frame);
                        if (!uLexua)
                        {
                            cout <<"Nuk u lexua dot frame. Programi po mbyllet!" << endl;
                            return -1;
                        }
                        framesTekaluara = cap.get(CV_CAP_PROP_POS_FRAMES); // updatohet numri i frames qe jane shfaqur
                        //levizet slideri me cdo 100 frames qe kalojne
                        setTrackbarPos("Pozicioni", "VideoDemo", cap.get(CV_CAP_PROP_POS_FRAMES)/100);
                        resize(*framePtr,*framePtr,Size(512,412), CV_INTER_AREA);
                        int tastIShtypur =-1;
                        if (zgjedhjaPerdoruesit == 49)
                        {
                            shtoTon.sepiaPerVideo(frame);
                        }
                        if (zgjedhjaPerdoruesit == 50)
                        {
                            cvtColor(frame, frame, CV_BGR2GRAY);
                        }
                        if (zgjedhjaPerdoruesit == 51)
                        {
                            bitwise_not(frame, frame);
                        }
                        double ndryshimiBrightenes = vleraSliderBrightenes*10-250;
                        double ndryshimiContrast = vleraSliderContrast*10/250.0;
                        frame.convertTo(frame,-1,ndryshimiContrast,ndryshimiBrightenes);
                        imshow("VideoDemo", frame);
                        tastIShtypur = waitKey(10);
                        if (tastIShtypur == 112)
                            waitKey(0);
                        else if (tastIShtypur == 49) zgjedhjaPerdoruesit = tastIShtypur;
                        else if (tastIShtypur == 50) zgjedhjaPerdoruesit = tastIShtypur;
                        else if (tastIShtypur == 51) zgjedhjaPerdoruesit = tastIShtypur;
                        else if (tastIShtypur == 98)
                        {
                            zgjedhjaPerdoruesit = tastIShtypur;
                            setTrackbarPos("Brightenes", "VideoDemo", 25);
                            setTrackbarPos("Contrast", "VideoDemo", 25);
                            vleraSliderBrightenes = 25;
                            vleraSliderContrast = 25;
                        }
                        else if (tastIShtypur == 27)
                        {
                            cout << "Dritarja po mbyllet"<< endl;
                            break;
                        }
                    }
                    destroyAllWindows();
                }
                break; //end case 2
                case 49: //zgjedh te hape foto
                {
                shfaqMenu.menuFoto();
                
                    cout << "Ju lutem jepni filepath te PLOTE te file qe doni te hapni." <<endl;
                    string filepath;
                    cin.ignore(); //behet flush console sepse mund te kete karaktere '/n' te cilat perfundojne funksionin getline pa e marre inputin.
                    getline(cin, filepath);
                    cout << filepath <<endl;
                //lexohet imazhi ne strukturen Mat te openCV. Mat - matrice qe mund te marre deri ne 4 dimensione. Varet nga numri i kanaleve te pixelave dhe nga faktore te tjere
                Mat img = imread(filepath);//vendoset filepath plote
                Mat *imgptr = &img;
                if (img.empty())
                {
                    cout << "Ngarkimi nuk u krye me sukses. Programi po mbyllet" << endl;
                    cout << "Hint: Kontrollo filepath"<< endl;
                    return -1;
                }
                else cout << "Ngarkimi u krye me sukses" <<endl;
                img.convertTo(img, CV_8U); // pixelat konvertohen ne pixela unsigned char me 3 kanale dhe 3 bite
                resize(*imgptr,*imgptr,Size(512,512),  CV_INTER_AREA);
                string dritarja = "Demo Foto"; // emri i dritares ku shfaqet fotoja
                namedWindow(dritarja,CV_WINDOW_NORMAL);
                imshow(dritarja,img);
                //kopjohet fotoja origjinale ne data members fotoOrigjinale te seciles prej klasave qe do te ndryshojne foton
                shtoTon.fotoOrigjinale = img.clone();
                shtoEfekt.fotoOrigjinale = img.clone();
                edit.fotoOrigjinale = img.clone();
                int efektiParaardhes = -1;
                    zgjedhjaPerdoruesit = -1;
                while (true){ // futet ne nje cikel qe e lejon user te ndryshoje foton duke shtypur butona
                    int tastIshtypur= waitKey(20);
                    if (zgjedhjaPerdoruesit == 49) //kerkon sepia
                    {
                        //nqs imazhi ka qene negativ ose bardhe e zi kthehet ne origjinal njehere
                        //sepia nuk mund te punoje me formatet e mesiperme
                        if (efektiParaardhes == 50){
                            shtoEfekt.goBack(img);
                        }
                        shtoTon.sepia(*imgptr,dritarja);
                        tastIshtypur = waitKey(0);//ndalet ekzekutimi derisa te shtypet buton tjeter
                        zgjedhjaPerdoruesit = -1;
                        efektiParaardhes = 49;
                    }
                    else if (zgjedhjaPerdoruesit == 50) // zgjedh bardhe e zi
                    {
                        if (efektiParaardhes == 51)
                            shtoEfekt.goBack(img);
                        if(efektiParaardhes == 50)
                        {}
                        else {
                        cvtColor(img, img, CV_BGR2GRAY);
                        imshow(dritarja,img);
                        tastIshtypur = waitKey(0);
                        zgjedhjaPerdoruesit = -1;
                            efektiParaardhes = 50;}
                    }
                    else if (zgjedhjaPerdoruesit == 51) // zgjedh negative (invertimin e ngjyrave)
                    {
                        if (efektiParaardhes == 50)
                            shtoEfekt.goBack(img);
                        bitwise_not(img, img);
                        imshow(dritarja,img);
                        tastIshtypur = waitKey(0);
                        zgjedhjaPerdoruesit = -1;
                        efektiParaardhes = 51;
                    }
                    else if (zgjedhjaPerdoruesit == 52) //zgjedh blur / smooth
                    {
                        shtoEfekt.Blur_Or_Smooth(*imgptr, dritarja);
                        zgjedhjaPerdoruesit = -1;
                        destroyWindow(dritarja);
                    }
                    else if (zgjedhjaPerdoruesit == 98) // zgjedh te kthehet ne foton origjinale
                    {
                        shtoEfekt.goBack(img);
                        imshow(dritarja,img);
                        zgjedhjaPerdoruesit =-1;
                    }
                    else if (zgjedhjaPerdoruesit == 99) // zgjedh te ndryshoje kontrastin dhe brightenesin
                    {
                        if (efektiParaardhes == 51)
                            shtoEfekt.goBack(img);
                        shtoEfekt.Contrast_Brightenes(*imgptr, dritarja);
                        zgjedhjaPerdoruesit =-1;
                        destroyWindow(dritarja);
                    }
                    else if (zgjedhjaPerdoruesit == 114) // zgjedh te beje rotate imazhin
                    {
                        edit.rotullo(*imgptr, dritarja);
                        zgjedhjaPerdoruesit = -1;
                        destroyWindow(dritarja);
                    }
                    else if (zgjedhjaPerdoruesit == 115) // zgjedh sharpen
                    {
                        if (efektiParaardhes == 51) //shihet nqs ka qene i invertuar
                            shtoEfekt.goBack(img);
                        shtoEfekt.Sharpen(*imgptr);
                        imshow(dritarja, img);
                        tastIshtypur = waitKey(0);
                        zgjedhjaPerdoruesit = -1;
                    }
                    else if (zgjedhjaPerdoruesit == 27) // zgjedh te mbylle foton
                    {
                        cout << "Deshironi te ruani foton? ('y' = po; 'n' = jo)" <<endl;
                        int ruaj = waitKey(0);
                        destroyWindow(dritarja);
                        if (ruaj == 121){ //zgjedh y
                            cout << "Ju lutem jepni filepath ku doni te ruani imazhin." <<endl;
                            string filepathRuajtje;
                            cin.ignore();
                            getline(cin, filepathRuajtje);
                            string s1 = "/";
                            filepathRuajtje = s1+filepathRuajtje;
                            cout << filepathRuajtje<<endl;
                            //specifikohet se si do te ruhet imazhi
                            vector<int> parametrat_e_ruajtjes;
                            parametrat_e_ruajtjes.push_back(CV_IMWRITE_JPEG_QUALITY);
                            parametrat_e_ruajtjes.push_back(97); // 0 - 100 sa me i larte aq me mire
                            // thirret funksioni imwrite te cilit i jepen filepath ku do te ruhet,
                            // imazhi qe do te ruhet
                            // menyra se si do te ruhet
                            bool uRuajt = imwrite (filepathRuajtje,img,parametrat_e_ruajtjes);
                            if (uRuajt) // nese imwrite kthen true
                                cout << "Imazhi u ruajt me sukses." <<endl;
                            else cout << "Imazhi nuk u ruajt." <<endl;
                        }
                        cout << "Dritarja po mbyllet" <<endl;
                        zgjedhjaPerdoruesit = -1;
                        break; //mbasi ruhet ose jo dilet nga cikli
                    }
                    if (tastIshtypur == 49) zgjedhjaPerdoruesit = tastIshtypur;// 1
                    else if (tastIshtypur == 27) zgjedhjaPerdoruesit = tastIshtypur;//ESC
                    else if (tastIshtypur == 50) zgjedhjaPerdoruesit = tastIshtypur;// 2
                    else if (tastIshtypur == 51) zgjedhjaPerdoruesit = tastIshtypur;// 3
                    else if (tastIshtypur == 52) zgjedhjaPerdoruesit = tastIshtypur;// 4
                    else if (tastIshtypur == 98) zgjedhjaPerdoruesit = tastIshtypur;// b
                    else if (tastIshtypur == 99) zgjedhjaPerdoruesit = tastIshtypur;// c
                    else if (tastIshtypur == 114) zgjedhjaPerdoruesit = tastIshtypur;// r
                    else if (tastIshtypur == 115) zgjedhjaPerdoruesit = tastIshtypur;// s
                    namedWindow(dritarja); // krijohet e njejta dritare sepse ne disa prej funksioneve ajo shkaterrohet
                    imshow(dritarja,img);
                } //end while
            } //end case 1
                break;
            default: // nga menuja kryesore nuk zgjedh 1 ose 2
                ekzekutimi = -1;
                break;
            }//end switch
            cout << "Shtypni 'M' per tu kthyer ne menune kryesore, 'ESC' per te dale nga programi ose cdo buton tjeter per te vazhduar me veprimin aktual" << endl;
            namedWindow("Zgjidh");
            int butShtypur = waitKey(0);
            if (butShtypur == 109){ //shtypet 'm'
                destroyWindow("Zgjidh");
                break; // dilet nga while dhe vazhdohet ekzekutimi tek while i pare (shfaqja e menuse kryesore
            }
            if (butShtypur == 27) // shtypet ESC
            {
                ekzekutimi = -1; //qe te mos ekzekutohet as while i pare
                cout << "Programi po mbyllet!" <<endl;
                destroyWindow("Zgjidh");
                break; // dilet nga while
            }
        }//end while 2
    }//end while 1
    return 0;
}//end main







