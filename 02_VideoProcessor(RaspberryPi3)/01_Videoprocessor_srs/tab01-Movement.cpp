#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;

// Tab01 Frame Image
void MainWindow::QImage_tab01(Mat frame_org){
    QImage QImage_tab01(frame_org.data, frame_org.cols, frame_org.rows, frame_org.step,
                QImage::Format_RGB888);
    pixmap_tab01_Movement.setPixmap(QPixmap::fromImage(QImage_tab01.rgbSwapped()));
    ui->graphicsView_tab01_Movement->fitInView(&pixmap_tab01_Movement, Qt::KeepAspectRatio);}

// ROTATE
void MainWindow::on_RrBtn_pressed()     // 회전 + 시계방향, - 반시계방향
{   ui->graphicsView_tab01_Movement->rotate(10);
//    ui->graphicsView_tab01_Movement->rotate()
}

void MainWindow::on_RlBtn_pressed()     // 회전 + 시계방향, - 반시계방향
{   ui->graphicsView_tab01_Movement->rotate(-10);}

void MainWindow::on_HOMEBtn_pressed()   // 원래 크기와 위치로
{
    ui->graphicsView_tab01_Movement->move(80, 40);    // 위치 잡고 수정하자
    ui->graphicsView_tab01_Movement->setFixedSize(320, 240);
    ui->graphicsView_tab01_Movement->resetMatrix();
//    ui->graphicsView_tab01_Movement->resize(320, 240);
}

// MOVEMENT
# define movenum 6
void MainWindow::on_UpBtn_pressed()     // 위로 이동
{   ui->graphicsView_tab01_Movement->move(ui->graphicsView_tab01_Movement->x(),ui->graphicsView_tab01_Movement->y()-movenum);}

void MainWindow::on_RightBtn_pressed()  // 우측 이동
{   ui->graphicsView_tab01_Movement->move(ui->graphicsView_tab01_Movement->x()+movenum,ui->graphicsView_tab01_Movement->y());}

void MainWindow::on_LeftBtn_pressed()   // 좌측 이동
{   ui->graphicsView_tab01_Movement->move(ui->graphicsView_tab01_Movement->x()-movenum, ui->graphicsView_tab01_Movement->y());}

void MainWindow::on_DownBtn_pressed()   // 아래로 이동
{   ui->graphicsView_tab01_Movement->move(ui->graphicsView_tab01_Movement->x(),ui->graphicsView_tab01_Movement->y()+movenum);}

// Change size
void MainWindow::on_EXTENDBtn_pressed() // 크기 확대
{   ui->graphicsView_tab01_Movement->setFixedSize(ui->graphicsView_tab01_Movement->width()+5,ui->graphicsView_tab01_Movement->height()+5);}

void MainWindow::on_REDUCEBtn_pressed() // 크기 축소
{   ui->graphicsView_tab01_Movement->setFixedSize(ui->graphicsView_tab01_Movement->width()-5,ui->graphicsView_tab01_Movement->height()-5);}


