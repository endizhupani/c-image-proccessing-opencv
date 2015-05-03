//
//  ToneNgjyrash.cpp
//  Projekt Endi Zhupani IE206 Image Processing
//  File me deklarimet e funksioneve qe perdoren per te perpunuar fotot

#include "PerpunimFotosh.h"
// i jep ngjyrave te fotos tonin "sepia"
void ToneNgjyrash :: sepia(Mat &foto, string emriDritares)
{
    //Matrica qe do kalohet neper imazh duke ndryshuar zecilin prej pixelave bazuar ne vleren e matrices
    //per te arritur tonin sepia
    Mat kern = (cv::Mat_<float>(4,4) <<  0.2, 0.534, 0.131, 0,
                0.349, 0.686, 0.168, 0,
                0.393, 0.769, 0.189, 0,
                0, 0, 0, 1);
    transform(foto,foto,kern);//transformon foton ne Sepia
    imshow(emriDritares,foto);//shfaq foton ne dritare.
}
void ToneNgjyrash:: sepiaPerVideo(Mat &frame)
{
    //Matrica qe do kalohet neper imazh duke ndryshuar zecilin prej pixelave bazuar ne vleren e matrices
    //per te arritur tonin sepia
    Mat kern = (cv::Mat_<float>(4,4) <<  0.2, 0.534, 0.131, 0,
                0.349, 0.686, 0.168, 0,
                0.393, 0.769, 0.189, 0,
                0, 0, 0, 1);
    transform(frame,frame,kern);//transformon foton ne Sepia
}
/* Krijon nje imazh ne formatin IplImage (format i perdurur nga versione te vjetra te openCV) 
   identik me imazhMat qe eshte ne formatin Mat
*/
void Efekte::Contrast_Brightenes(Mat &foto, string emriDritares)
{
    Mat fotoParaardhese = foto.clone(); // kjo variabel mban kopje te fotos para ndryshimit te fundit.
    cout << "Shtypni ESC per te caktivizuar efektin" <<endl;
    int vleraSliderBrightenes = 250; //vlera fillestare ne slider
    int vleraSliderContrast = 250;
    //krijohen nje sliderat ne dritaren e mesiperme per te rregulluar brightenes dhe contrast; me hapesire vlerash 0-500 dhe me vlere fillestare @int vleraSliderBrightenes.
    createTrackbar("Brightenes", emriDritares, &vleraSliderBrightenes, 500);
    createTrackbar("Contrast", emriDritares, &vleraSliderContrast, 500);
    while (true){
        int ndryshimiBrightenes = vleraSliderBrightenes-250;//vlera me te cilen ndryshon brightenes
        double ndryshimiContrast = vleraSliderContrast/250.0;//vlera me te cilen ndryshon kontrasti
        foto = fotoParaardhese.clone();
        foto.convertTo(foto,-1,ndryshimiContrast,ndryshimiBrightenes); //behet konvertimi sipas brightenes dhe contrast te kerkuar
        imshow(emriDritares, foto);
        int iKey = waitKey(50);//pritet per nje shtypje butoni dhe i jepet kohe programit per te gjeneruar foton e ndryshuar
        if (iKey == 27){ //shtypet ESC
            cout << "Efekti u caktivizua" <<endl;
            break;
        }
    }
}
/*
 ben sharpen te imazhit duke perdorur formule te gatshme per llogaritjen e pixelave.
 */
void Efekte::Sharpen(Mat& Imazh)
{
    Mat ImazhiNdihmes; //duhet per te kryer Sharpen.
    CV_Assert(Imazh.depth() == CV_8U); //pranohen vetem pixela te tipit unsigned char 8 bit
    
    ImazhiNdihmes.create(Imazh.size(), Imazh.type());
    const int nrKanaleve = Imazh.channels();
    
    for(int j = 1; j < Imazh.rows - 1; ++j)
    {
        //merren shenjusa per pixelin aktual dhe ato fqinje
        const uchar* pixParaardhes = Imazh.ptr<uchar>(j - 1);
        const uchar* pixAktual  = Imazh.ptr<uchar>(j    );
        const uchar* pixPasardhes     = Imazh.ptr<uchar>(j + 1);
        //shenjues per pixelin qe do i ndryshohet vlera
        uchar* pixNdryshuar = ImazhiNdihmes.ptr<uchar>(j);
        
        for(int i = nrKanaleve; i < nrKanaleve * (Imazh.cols - 1); ++i)
        {
            /*
             pixeli i ndryshuar llogaritet sipas formules se gatshme per te bere sharpen te imazhit
             */
            *pixNdryshuar++ = saturate_cast<uchar>(5 * pixAktual[i]
                                             -pixAktual[i - nrKanaleve] - pixAktual[i + nrKanaleve] - pixParaardhes[i] - pixPasardhes[i]);
        }
    }
    /*
     pixelat kufi vendosen 0 (ngjyre e zeze) sepse formula nuk vlen per to duke qene se mund
     te mos kene pixela parardhes ose pasardhes.
     */
    ImazhiNdihmes.row(0).setTo(Scalar(0));
    ImazhiNdihmes.row(ImazhiNdihmes.rows - 1).setTo(Scalar(0));
    ImazhiNdihmes.col(0).setTo(Scalar(0));
    ImazhiNdihmes.col(ImazhiNdihmes.cols - 1).setTo(Scalar(0));
    Imazh = ImazhiNdihmes.clone();//kopjohet imazhi ndihmes.
}
/* Merr si parametra nje imazh ne format Mat dhe nje string dhe e shfaq imazhin e bere blur ne 
   ne dritaren me emer @param emriDritares. Blur behet duke rreshkitur nje matrice katrore te 
   rendit n > 1(n tek) mbi imazh sipas metodes "Median Blur". 
   Shkalla me te cilen behen blur kontrollohet nga madhesia e matrices
   e cila caktohet nga perduruesi duke perdorur nje trackbar
 */
void Efekte::Blur_Or_Smooth(Mat &Imazh, string emriDritares)
{
    int vleraSliderBlur = 2; //vlera fillestare ne trackbar
    createTrackbar("Blur", emriDritares, &vleraSliderBlur, 41);
    cout << "Shtypni ESC per te caktivizuar blur" <<endl;
    while (true)
    {
        int madhesiaKernelit; //logaritet duke perdorur vleraSliderBlur
        if (vleraSliderBlur <=2){ // nuk behet dot blur sepse e do madhesine te pakten 3.
            goBack(Imazh);
        }
        else if ((vleraSliderBlur>2)&&(vleraSliderBlur%2 == 0)){ //nqs eshte >2 dhe cift
            goBack(Imazh); //shkohet si fillim ne foton origjinale
            madhesiaKernelit = vleraSliderBlur+1;
            medianBlur(Imazh,Imazh,madhesiaKernelit);
        }
        else if (vleraSliderBlur>2){ //nqs eshte > 2 dhe tek
            goBack(Imazh);
            madhesiaKernelit = vleraSliderBlur;
            medianBlur(Imazh,Imazh,madhesiaKernelit);
        }
        
        imshow(emriDritares, Imazh); // shfaqet imazhi ne dritare
        int key = waitKey(50);
        if (key==27)
        {
            cout << "Efekti u caktivizua";
            break;
        }
        
    }
    return;
}
//funksion qe heq te gjitha efektet ne nje foto
void Efekte::goBack(Mat &fotoNdryshuar)
{
    fotoNdryshuar = fotoOrigjinale.clone();
}
/*Ben rotate te imazhit sipas nje kendi qe kontrollohet me ane te nje trackbari (-180 <= kendi <= 180)
  dhe e shfaq kete imazh ne dritaren me emer @param emriDritares
 */
void Editim::rotullo(Mat& imazhOrig, string emriDritares)
{
    int vleraSliderRotate = 180;
    createTrackbar("Rotate", emriDritares, &vleraSliderRotate, 360);
    while (true){
        double kendi = vleraSliderRotate-180; //hiqet 180 per te marre vlera -180 deri 180
        imazhOrig = fotoOrigjinale.clone(); //sigurohet qe rotullimi te aplikohet mbi imazhin origjinal
                                            //perndryshe kemi rrotullime te pafundme
        int gjatesia = max(imazhOrig.cols, imazhOrig.rows); //permasa e imazhit pas rrotullimit
        Point2f pikaBaze(gjatesia/2.0, gjatesia/2.0); //pika sipas te ciles behet rrotullimi (qendra)
        Mat matriceRrotullimi = getRotationMatrix2D(pikaBaze, kendi, 1.0); //llogaritet matrica
                                                                           //me te cilen behet rrotullimi
        //transformohet imazhi sipas kesaj matrice
        warpAffine(imazhOrig, imazhOrig, matriceRrotullimi, Size(gjatesia, gjatesia));
        imshow(emriDritares, imazhOrig);
        int tastIshtypur = waitKey(50);
        if (tastIshtypur == 27)
        {
            cout << "Rrotullimi caktivizohet. " <<endl;
            break;
        }
    }
    return;
}















