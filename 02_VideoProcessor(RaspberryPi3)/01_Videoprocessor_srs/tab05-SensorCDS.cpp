#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <wiringPi.h>
using namespace cv;
using namespace std;
#include <wiringPi.h>       // 라즈베리 파이
#include <wiringPiSPI.h>
#include <map>
#define CS_MCP3008 10
#define SPI_CHANNEL 0
#define SPI_SPEED 1000000
int brightness = 0;
int adcChannel = 0;
int adcValue = 0;
using namespace cv;
using namespace std;

int read_mcp3008_adc(unsigned char adcChannel) {
    unsigned char buff[3];
    int adcValue = 0;
    buff[0] = 0x01;
    buff[1] = 0x80|((adcChannel & 0x07) << 4);
    buff[2] = 0x00;
    digitalWrite(CS_MCP3008, 0);
    wiringPiSPIDataRW(SPI_CHANNEL, buff, 3);
    buff[1] = 0x03 & buff[1];
    adcValue = (buff[1] << 8)|buff[2];
    digitalWrite(CS_MCP3008, 1);
    return adcValue;
}


void MainWindow::QImage_tab05(Mat frame_SensorCDS, Mat frame_org)
{
    wiringPiSetup();
    pinMode(CS_MCP3008, OUTPUT);
    wiringPiSPISetup(SPI_CHANNEL, SPI_SPEED);

    adcChannel = 3;
    adcValue = read_mcp3008_adc(adcChannel);
    delay(300);
    adcValue = adcValue - 512;

    frame_org.convertTo(frame_SensorCDS, -1, 1, adcValue);
    QImage QImage_tab05(frame_SensorCDS.data, frame_SensorCDS.cols, frame_SensorCDS.rows, frame_SensorCDS.step, QImage::Format_RGB888);
    pixmap_tab05_SensorCDS.setPixmap( QPixmap::fromImage(QImage_tab05.rgbSwapped()));

    ui->graphicsView_tab05_SensorCDS->fitInView(&pixmap_tab05_SensorCDS, Qt::KeepAspectRatio);

    ui->SensorValues->display(adcValue);
}
