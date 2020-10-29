#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;



void MainWindow::QImage_tab04()
{
    Mat frame_detect;
    video >> frame_detect;
    CascadeClassifier classifier;
    ui->checkBox_Detect_face->setCheckable(1);
    ui->checkBox_Detect_car->setCheckable(1);

    if(ui->checkBox_Detect_car->isChecked()){
        ui->checkBox_Detect_face->setCheckable(0);

        classifier.load("./detect/haarcascade_cars.xml");
        vector<Rect> detects;
        classifier.detectMultiScale(frame_detect, detects);
        for(Rect rc : detects) {
            rectangle(frame_detect, rc, Scalar(0, 0, 255), 2);
        }
        QImage QImage_tab04_Detect(frame_detect.data, frame_detect.cols, frame_detect.rows, frame_detect.step, QImage::Format_RGB888);
        pixmap_tab04_Detect.setPixmap( QPixmap::fromImage(QImage_tab04_Detect.rgbSwapped()));
        ui->graphicsView_tab04_Detect->fitInView(&pixmap_tab04_Detect, Qt::KeepAspectRatio);
    }

    if(ui->checkBox_Detect_face->isChecked()){
        ui->checkBox_Detect_car->setCheckable(0);
        classifier.load("./detect/haarcascade_frontalface_default.xml");
        vector<Rect> detects;
        classifier.detectMultiScale(frame_detect, detects);
        for(Rect rc : detects) {
            rectangle(frame_detect, rc, Scalar(255, 0, 0), 2);
        }
        QImage QImage_tab04_Detect(frame_detect.data, frame_detect.cols, frame_detect.rows, frame_detect.step, QImage::Format_RGB888);
        pixmap_tab04_Detect.setPixmap( QPixmap::fromImage(QImage_tab04_Detect.rgbSwapped()));
        ui->graphicsView_tab04_Detect->fitInView(&pixmap_tab04_Detect, Qt::KeepAspectRatio);
    }
}
