#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>

static QImage img(500, 500, QImage::Format_RGB888);
static QRgb bgColor(qRgb(0, 0, 0));

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->display->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda_algo(int x1, int y1, int x2, int y2)
{
    QRgb value;
    value = qRgb(0, 230, 230);
    int length = 0;
    if (abs(x2 - x1) >= abs(y2 - y1)){
        length = abs(x2 - x1);
    }
    else {
        length = abs(y2 - y1);
    }
    float dx = float(x2 - x1)/float(length);
    float dy = float(y2 - y1)/float(length);
    float x = x1;
    float y = y1;
    int i = 1;
    while (i <= length){
        img.setPixel(x, y, value);
        x = x + dx;
        y = y + dy;
        i++;
    }
}

void MainWindow::bresenham_circle(int xc, int yc, int r)
{
    QRgb value;     //set colour of pixel
    value = qRgb(255,255,0);
    int x=0;    //start at point (0,r)
    int y=r;
    int D = 3 - (2*r);  //initial decision parameter
    while(x<=y){
        //set pixels in all 8 octants
        img.setPixel(y+xc, x+yc, value);
        img.setPixel(x+xc, y+yc, value);
        img.setPixel(-x+xc, y+yc, value);
        img.setPixel(-y+xc, x+yc, value);
        img.setPixel(-y+xc, -x+yc, value);
        img.setPixel(-x+xc, -y+yc, value);
        img.setPixel(x+xc, -y+yc, value);
        img.setPixel(y+xc, -x+yc, value);

        if (D<0){
            D = D + 4*x + 6;    //next decision parameter
        }
        else{
            D = D + 4*(x-y) + 10;   //next decision parameter
            y = y-1;
        }
        x = x+1;
    }
}

void MainWindow::midpoint_circle(int xc, int yc, int r)
{
    QRgb value;
    value = qRgb(255,0,255);
    int x=0;
    int y=r;
    float D = 1.25 - r;
    while(x<=y){
        //set pixels in all 8 octants
        img.setPixel(y+xc, x+yc, value);
        img.setPixel(x+xc, y+yc, value);
        img.setPixel(-x+xc, y+yc, value);
        img.setPixel(-y+xc, x+yc, value);
        img.setPixel(-y+xc, -x+yc, value);
        img.setPixel(-x+xc, -y+yc, value);
        img.setPixel(x+xc, -y+yc, value);
        img.setPixel(y+xc, -x+yc, value);

        if(D<0){
            D = D + 2*x + 3;
        }
        else{
            D = D + 2*(x-y) + 5;
            y = y-1;
        }
        x = x+1;
    }
}


void MainWindow::on_DDA_line_clicked()
{
    int x1 = ui->plainTextEdit->toPlainText().toInt();
    int y1 = ui->plainTextEdit_2->toPlainText().toInt();
    int x2 = ui->plainTextEdit_3->toPlainText().toInt();
    int y2 = ui->plainTextEdit_4->toPlainText().toInt();

    dda_algo(x1, y1, x2, y2);
    ui->display->setPixmap(QPixmap::fromImage(img));
    ui->display->show();
}

void MainWindow::on_B_Circle_clicked()
{
    int xc = ui->plainTextEdit_7->toPlainText().toInt();
    int yc = ui->plainTextEdit_6->toPlainText().toInt();
    int r  = ui->plainTextEdit_5->toPlainText().toInt();

    bresenham_circle(xc, yc, r);
    ui->display->setPixmap(QPixmap::fromImage(img));
    ui->display->show();
}

void MainWindow::on_M_Circle_clicked()
{
    int xc = ui->plainTextEdit_7->toPlainText().toInt();
    int yc = ui->plainTextEdit_6->toPlainText().toInt();
    int r  = ui->plainTextEdit_5->toPlainText().toInt();

    midpoint_circle(xc, yc, r);
    ui->display->setPixmap(QPixmap::fromImage(img));
    ui->display->show();
}

void MainWindow::on_create_1_clicked()
{
    //centre coordinates
    int xc = ui->plainTextEdit_7->toPlainText().toInt();
    int yc = ui->plainTextEdit_6->toPlainText().toInt();
    //outer circle radius
    int R  = ui->plainTextEdit_5->toPlainText().toInt();

    int s = (0.866)*R;  //half the side length of eq triangle
    int r = (0.5)*R;    //inner circle radius

    //draw triangle
    dda_algo(xc, yc - R, xc + s, yc + r);
    dda_algo(xc, yc - R, xc - s, yc + r);
    dda_algo(xc - s, yc + r, xc + s, yc + r);

    //draw circles
    bresenham_circle(xc, yc, R);
    midpoint_circle(xc, yc, r);

    ui->display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_create_2_clicked()
{
    //get diagonal coordinates of outer rectangle
    int x1 = ui->plainTextEdit->toPlainText().toInt();
    int y1 = ui->plainTextEdit_2->toPlainText().toInt();
    int x2 = ui->plainTextEdit_3->toPlainText().toInt();
    int y2 = ui->plainTextEdit_4->toPlainText().toInt();

    //half length and half breadth
    float s1 = abs((x1 - x2)/2.0);
    float s2 = abs((y1 - y2)/2.0);

    //centre coordinates
    float xc = x1 + s1;
    float yc = y1 + s2;

    //radius
    float r = s1 * (sin(atan2(s2, s1)));

    //draw outer rectangle
    dda_algo(x1, y1, x2, y1);
    dda_algo(x1, y1, x1, y2);
    dda_algo(x2, y2, x1, y2);
    dda_algo(x2, y2, x2, y1);

    //draw inner parallelogram
    dda_algo(x1 + s1, y1, x2, y1 + s2);
    dda_algo(x2, y1 + s2, x1 + s1, y2);
    dda_algo(x1 + s1, y2, x1, y1 + s2);
    dda_algo(x1, y1 + s2, x1 + s1, y1);

    //draw circle
    bresenham_circle(xc, yc, r);

    ui->display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_clear_clicked()
{
    img.fill(bgColor);
    ui->display->setPixmap(QPixmap::fromImage(img));
}


