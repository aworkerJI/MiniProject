#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QImage>
#include <QPixmap>
#include <QCloseEvent>
#include <QMessageBox>
#include <iostream>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdlib.h>
#include "opencv2/opencv.hpp"

using namespace cv;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void QImage_tab01(Mat frame_org);
    void QImage_tab02(Mat frame_rb, Mat frame_org, Mat frame_gb, Mat frame_rg);
    void QImage_tab03(Mat frame_org);
    void QImage_tab04();
    void QImage_tab05(Mat frame_SensorCDS, Mat frame_org);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    // mainwindow
    void on_STARTBtn_pressed();
    void on_RECBtn_pressed();
    void on_CAPTUREBtn_pressed();
    // tab01 Movement
    void on_RrBtn_pressed();
    void on_RlBtn_pressed();
    void on_HOMEBtn_pressed();
    void on_UpBtn_pressed();
    void on_RightBtn_pressed();
    void on_LeftBtn_pressed();
    void on_DownBtn_pressed();
    void on_EXTENDBtn_pressed();
    void on_REDUCEBtn_pressed();
    // tab02 SensorCDS
    void on_DARKBtn_pressed();
    void on_BRIGHTBtn_pressed();






private:
    Ui::MainWindow *ui;
    // tab01 Movement
    QGraphicsPixmapItem pixmap_tab01_Movement;
    // tab02 Divide
    QGraphicsPixmapItem pixmap_tab02_Red;
    QGraphicsPixmapItem pixmap_tab02_Green;
    QGraphicsPixmapItem pixmap_tab02_Blue;
    QGraphicsPixmapItem pixmap_tab02_RG;
    QGraphicsPixmapItem pixmap_tab02_RB;
    QGraphicsPixmapItem pixmap_tab02_GB;
    // tab03 Histo
    QGraphicsPixmapItem pixmap_tab03_Red;
    QGraphicsPixmapItem pixmap_tab03_Green;
    QGraphicsPixmapItem pixmap_tab03_Blue;
    QGraphicsPixmapItem pixmap_tab03_HistoRed;
    QGraphicsPixmapItem pixmap_tab03_HistoGreen;
    QGraphicsPixmapItem pixmap_tab03_HistoBlue;
    // tab04 Detect
    QGraphicsPixmapItem pixmap_tab04_Detect;

    // tab05 SensorCDS
    QGraphicsPixmapItem pixmap_tab05_SensorCDS;
    cv::VideoCapture video;
};
void calc_Histo(const Mat&, Mat&, int, int);
void draw_histo(Mat, Mat&, Size);

#endif // MAINWINDOW_H
