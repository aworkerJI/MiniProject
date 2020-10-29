#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;

void MainWindow::QImage_tab02(Mat frame_rb, Mat frame_org, Mat frame_gb, Mat frame_rg)

{
    Mat bgr[3];
    split(frame_org, bgr);
    frame_rg = bgr[2]/2 + bgr[1]/2;     // red + green
    frame_rb = bgr[2]/2 + bgr[0]/2 ;    // red + blue
    frame_gb = bgr[1]/2 + bgr[0]/2;     // green + blue
    QImage QImage_tab02_Red(bgr[2].data, bgr[2].cols, bgr[2].rows, bgr[2].step,
                            QImage::Format_Grayscale8);         //red bgr[2]
    pixmap_tab02_Red.setPixmap( QPixmap::fromImage(QImage_tab02_Red));
    ui->graphicsView_tab02_Red->fitInView(&pixmap_tab02_Red, Qt::KeepAspectRatio);
    QImage QImage_tab02_Green(bgr[1].data, bgr[1].cols, bgr[1].rows, bgr[1].step,
                            QImage::Format_Grayscale8);         //green bgr[1]
    pixmap_tab02_Green.setPixmap( QPixmap::fromImage(QImage_tab02_Green) );
    ui->graphicsView_tab02_Green->fitInView(&pixmap_tab02_Green, Qt::KeepAspectRatio);
    QImage QImage_tab02_blue(bgr[0].data, bgr[0].cols, bgr[0].rows, bgr[0].step,
                            QImage::Format_Grayscale8);         //blue bgr[0]
    pixmap_tab02_Blue.setPixmap( QPixmap::fromImage(QImage_tab02_blue));
    ui->graphicsView_tab02_Blue->fitInView(&pixmap_tab02_Blue, Qt::KeepAspectRatio);
    QImage QImage_tab02_RG(frame_rg.data, frame_rg.cols, frame_rg.rows, frame_rg.step,
                            QImage::Format_Grayscale8);         //red + green
    pixmap_tab02_RG.setPixmap( QPixmap::fromImage(QImage_tab02_RG));
    ui->graphicsView_tab02_RG->fitInView(&pixmap_tab02_RG, Qt::KeepAspectRatio);
    QImage QImage_tab02_RB(frame_rb.data, frame_rb.cols, frame_rb.rows, frame_rb.step,
                            QImage::Format_Grayscale8);         //green + blue
    pixmap_tab02_RB.setPixmap( QPixmap::fromImage(QImage_tab02_RB));
    ui->graphicsView_tab02_RB->fitInView(&pixmap_tab02_RB, Qt::KeepAspectRatio);
    QImage QImage_tab02_GB(frame_gb.data, frame_gb.cols, frame_gb.rows, frame_gb.step,
                            QImage::Format_Grayscale8);         // blue + red
    pixmap_tab02_GB.setPixmap( QPixmap::fromImage(QImage_tab02_GB));
    ui->graphicsView_tab02_GB->fitInView(&pixmap_tab02_GB, Qt::KeepAspectRatio);}
