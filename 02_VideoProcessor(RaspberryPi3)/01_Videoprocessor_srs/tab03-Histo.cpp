#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace cv;
using namespace std;

void calc_Histo(const Mat& frame, Mat& hist, int bins, int range_max = 256) {
    int histSize[] = {bins};
    float range[] = {0, (float)range_max};
    int channels[] = {0};
    const float* ranges[] = {range};

    calcHist(&frame, 1, channels, Mat(), hist, 1, histSize, ranges);
}

Mat  make_palatte(int rows, int num)
{   Mat hsv(rows, 1, CV_8UC3);
    for (int i = 0; i < rows; i++){
//        uchar hue = saturate_cast<uchar>((float)i / rows * 180);
        if(num == 1){
            hsv.at<Vec3b>(i) = Vec3b(0, 0, 255);
        }
        else if(num == 2){
            hsv.at<Vec3b>(i) = Vec3b(0, 255, 0);
        }
        else if(num == 3){
            hsv.at<Vec3b>(i) = Vec3b(255, 0, 0);
        }


    }
    cvtColor(hsv, hsv, COLOR_BGR2RGB);
    return hsv;
}

void draw_histo(Mat hist, Mat&hist_frame, Size size = Size(256, 200), int a = 0) {
    Mat hist_palatte = make_palatte(hist.rows, a);
    hist_frame = Mat(size, CV_8UC3, Scalar(255, 255, 255));
    float bin = (float)hist_frame.cols / hist.rows;
    normalize(hist, hist, 0, hist_frame.rows, NORM_MINMAX);
    for(int i = 0; i < hist.rows; i++){
        float start_x = i * bin;
        float end_x = (i + 1) * bin;
        Point2f pt1(start_x, 0);
        Point2f pt2(end_x, hist.at<float>(i));

        Scalar color = hist_palatte.at<Vec3b>(i);
        if(pt2.y > 0){
            rectangle(hist_frame, pt1, pt2, color, -1);
        }
    }
    flip(hist_frame, hist_frame, 0);
}

void MainWindow::QImage_tab03(Mat frame_org)
{
    Mat r_hist, g_hist, b_hist;
    Mat frame_r_hist, frame_g_hist, frame_b_hist;
    Mat bgr[3];
    split(frame_org, bgr);
    Size size = Size(256, 200);
    calc_Histo(bgr[2], r_hist, 256, 256);
    draw_histo(r_hist, frame_r_hist, size, 1);
    calc_Histo(bgr[1], g_hist, 256, 256);
    draw_histo(g_hist, frame_g_hist, size, 2);
    calc_Histo(bgr[0], b_hist, 256, 256);
    draw_histo(b_hist, frame_b_hist, size, 3);

    QImage QImage_tab03_Red(bgr[2].data, bgr[2].cols, bgr[2].rows, bgr[2].step,
                            QImage::Format_Grayscale8);         //red bgr[2]
    pixmap_tab03_Red.setPixmap( QPixmap::fromImage(QImage_tab03_Red));
    ui->graphicsView_tab03_Red->fitInView(&pixmap_tab03_Red, Qt::KeepAspectRatio);

    QImage QImage_tab03_Green(bgr[1].data, bgr[1].cols, bgr[1].rows, bgr[1].step,
                            QImage::Format_Grayscale8);         //green bgr[1]
    pixmap_tab03_Green.setPixmap( QPixmap::fromImage(QImage_tab03_Green));
    ui->graphicsView_tab03_Green->fitInView(&pixmap_tab03_Green, Qt::KeepAspectRatio);

    QImage QImage_tab03_blue(bgr[0].data, bgr[0].cols, bgr[0].rows, bgr[0].step,
                            QImage::Format_Grayscale8);         //blue bgr[0]
    pixmap_tab03_Blue.setPixmap( QPixmap::fromImage(QImage_tab03_blue));
    ui->graphicsView_tab03_Blue->fitInView(&pixmap_tab03_Blue, Qt::KeepAspectRatio);

    QImage QImage_tab03_HistoRed(frame_r_hist.data, frame_r_hist.cols, frame_r_hist.rows,
                                 frame_r_hist.step, QImage::Format_RGB888);
    pixmap_tab03_HistoRed.setPixmap( QPixmap::fromImage(QImage_tab03_HistoRed));
    ui->graphicsView_tab03_HistoRed->fitInView(&pixmap_tab03_HistoRed, Qt::KeepAspectRatio);

    QImage QImage_tab03_HistoGreen(frame_g_hist.data, frame_g_hist.cols, frame_g_hist.rows,
                                   frame_g_hist.step, QImage::Format_RGB888);
    pixmap_tab03_HistoGreen.setPixmap( QPixmap::fromImage(QImage_tab03_HistoGreen));
    ui->graphicsView_tab03_HistoGreen->fitInView(&pixmap_tab03_HistoGreen, Qt::KeepAspectRatio);

    QImage QImage_tab03_HistoBlue(frame_b_hist.data, frame_b_hist.cols, frame_b_hist.rows,
                                  frame_b_hist.step, QImage::Format_RGB888);
    pixmap_tab03_HistoBlue.setPixmap( QPixmap::fromImage(QImage_tab03_HistoBlue));
    ui->graphicsView_tab03_HistoBlue->fitInView(&pixmap_tab03_HistoBlue, Qt::KeepAspectRatio);
}
