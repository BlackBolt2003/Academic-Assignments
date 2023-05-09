#include "koch_curve.h"
#include "ui_koch_curve.h"
#include <math.h>

QImage img(500, 500, QImage::Format_RGB888);
QColor bgColor(qRgb(0,0,0));
QColor color(qRgb(230, 230, 230));

int it=0;

koch_curve::koch_curve(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::koch_curve)
{
    ui->setupUi(this);
    img.fill(bgColor);
    ui->display->setPixmap(QPixmap::fromImage(img));
}

koch_curve::~koch_curve()
{
    delete ui;
}

void koch_curve::dda(float x1,float y1,float x2,float y2){
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
        img.setPixelColor(x, y, color);
        x = x + dx;
        y = y + dy;
        i++;
    }
    ui->display->setPixmap(QPixmap::fromImage(img));
}

void koch_curve::drawCurve(int it, int x1, int y1, int x2, int y2)
{
    //base case
    if(it == 0){
        dda(x1, y1, x2, y2);
    }

    else{
        //draw curve
        int x3 = (2*x1 + x2)/3;
        int y3 = (2*y1 + y2)/3;

        int x4 = (x1 + 2*x2)/3;
        int y4 = (y1 + 2*y2)/3;

        int x5 = x3 + (x4 - x3)*(0.5) + (y4 - y3)*(0.86);
        int y5 = y3 - (x4 - x3)*(0.86) + (y4 - y3)*(0.5);

        drawCurve(it-1, x1, y1, x3, y3);
        drawCurve(it-1, x3, y3, x5, y5);
        drawCurve(it-1, x5, y5, x4, y4);
        drawCurve(it-1, x4, y4, x2, y2);
    }

}

void koch_curve::on_create_clicked()
{
    img.fill(bgColor);
    ui->display->setPixmap(QPixmap::fromImage(img));

    it = ui->level->toPlainText().toInt();
    drawCurve(it, 100, 250, 400, 250);

}
