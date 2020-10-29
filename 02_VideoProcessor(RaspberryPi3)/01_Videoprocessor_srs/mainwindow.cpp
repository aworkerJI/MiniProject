#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "opencv2/opencv.hpp"
#include <wiringPi.h>       // 라즈베리 파이
#include <wiringPiSPI.h>
#include <map>
#include <wiringPi.h>       // 라즈베리 파이
#include <wiringPiSPI.h>
#include <map>


#define CS_MCP3008 10
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000

using namespace cv;
using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this); //
    ui->graphicsView_tab01_Movement->setScene(new QGraphicsScene(this));        // Sets the current scene to scene.
    ui->graphicsView_tab01_Movement->scene()->addItem(&pixmap_tab01_Movement);  // Sets the view's current transformation matrix to matrix.

    ui->graphicsView_tab02_Red->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab02_Red->scene()->addItem(&pixmap_tab02_Red);
    ui->graphicsView_tab02_Green->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab02_Green->scene()->addItem(&pixmap_tab02_Green);
    ui->graphicsView_tab02_Blue->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab02_Blue->scene()->addItem(&pixmap_tab02_Blue);
    ui->graphicsView_tab02_RG->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab02_RG->scene()->addItem(&pixmap_tab02_RG);
    ui->graphicsView_tab02_RB->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab02_RB->scene()->addItem(&pixmap_tab02_RB);
    ui->graphicsView_tab02_GB->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab02_GB->scene()->addItem(&pixmap_tab02_GB);

    ui->graphicsView_tab03_Red->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab03_Red->scene()->addItem(&pixmap_tab03_Red);
    ui->graphicsView_tab03_Green->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab03_Green->scene()->addItem(&pixmap_tab03_Green);
    ui->graphicsView_tab03_Blue->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab03_Blue->scene()->addItem(&pixmap_tab03_Blue);
    ui->graphicsView_tab03_HistoRed->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab03_HistoRed->scene()->addItem(&pixmap_tab03_HistoRed);
    ui->graphicsView_tab03_HistoGreen->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab03_HistoGreen->scene()->addItem(&pixmap_tab03_HistoGreen);
    ui->graphicsView_tab03_HistoBlue->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab03_HistoBlue->scene()->addItem(&pixmap_tab03_HistoBlue);

    ui->graphicsView_tab04_Detect->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab04_Detect->scene()->addItem(&pixmap_tab04_Detect);

    ui->graphicsView_tab05_SensorCDS->setScene(new QGraphicsScene(this));
    ui->graphicsView_tab05_SensorCDS->scene()->addItem(&pixmap_tab05_SensorCDS);
}

MainWindow::~MainWindow(){
    delete ui;
}



void MainWindow::on_STARTBtn_pressed(){//on_startBtn_pressed() start
    if(video.isOpened()){
        ui->STARTBtn->setText("Start");
        video.release();
        return;
    }
    bool isCamera;
    int cameraIndex = ui->videoEdit->text().toInt(&isCamera);
    if(isCamera){
        if(!video.open(cameraIndex)){
            QMessageBox::critical(this,
                                  "Camera Error",
                                  "Make sure you entered a correct camera index,"
                                  "<br>or that the camera is not being accessed by another program!");
            return;
        }
    }
    else{
        if(!video.open(ui->videoEdit->text().trimmed().toStdString())){
            QMessageBox::critical(this,
                                  "Video Error",
                                  "Make sure you entered a correct and supported video file path,"
                                  "<br>or a correct RTSP feed URL!");
            return;
        }
    }
    ui->STARTBtn->setText("Stop");
    Mat frame_org, frame_gray, frame_BGR2HLS, frame_rg, frame_rb, frame_gb,  frame_detect, frame_SensorCDS;

    video.set(3,640);
    video.set(4,480);


    video >> frame_org;
    while(video.isOpened()){//while start
        video >> frame_org;
        CV_Assert(frame_org.data);
//        cvtColor(frame_org, frame_BGR2HLS, COLOR_BGR2HLS);
        // Converts an image from one color space to another where the source image is stored in two planes.
        if(ui->tabWidget->currentIndex() == 0) {
            QImage_tab01(frame_org);           // tab01-Movement
        }
        if(ui->tabWidget->currentIndex() == 1) {
            QImage_tab02(frame_rb, frame_org, frame_gb, frame_rg);
        }
        if(ui->tabWidget->currentIndex() == 2) {
            QImage_tab03(frame_org);
        }
        if(ui->tabWidget->currentIndex() == 3) {
            QImage_tab04();
        }
        if(ui->tabWidget->currentIndex() == 4) {

            QImage_tab05(frame_SensorCDS, frame_org);
        }




        qApp->processEvents();
    }//while end
    ui->STARTBtn->setText("Start");
}//on_startBtn_pressed() end

void MainWindow::closeEvent(QCloseEvent *event){
    if(video.isOpened()){
        QMessageBox::warning(this,"Warning","Stop the video before closing the application!");
        event->ignore();}
    else{
        event->accept();}
}

//
void MainWindow::on_RECBtn_pressed(){
    ui->RECBtn->setText("STOP");
    //    VideoCapture;
    Size size= Size((int)video.get(CAP_PROP_FRAME_WIDTH), (int)video.get(CAP_PROP_FRAME_HEIGHT));
    int  fourcc = VideoWriter::fourcc('H', '2', '6', '4');
    double fps = 10;
    int  delay = cvRound(1000.0 / fps);


    VideoWriter writer;
    writer.open("./REC/REC01.avi", fourcc, fps, size);

    wiringPiSetup();
    pinMode(26, OUTPUT);
    while(1){
        Mat frame_rec;
        video >> frame_rec;
        writer << frame_rec;
        imshow("rec", frame_rec);
        digitalWrite(26,1);
        if(waitKey(delay)>=0){
            digitalWrite(26,0);
            break;
        }
    }
    writer.release();
    destroyWindow("rec");
    ui->RECBtn->setText("REC");
}

void MainWindow::on_CAPTUREBtn_pressed(){
    Mat frame_capture;
    video >> frame_capture;
    imwrite("./CAP/CAP01.jpg", frame_capture);
    imshow("capture",frame_capture);
    waitKey(0);
    destroyWindow(("capture"));
}




void MainWindow::on_BRIGHTBtn_pressed(){
}

void MainWindow::on_DARKBtn_pressed(){
}




