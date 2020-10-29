#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/face.hpp>
using namespace cv;
using namespace std;


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    return a.exec();

}
