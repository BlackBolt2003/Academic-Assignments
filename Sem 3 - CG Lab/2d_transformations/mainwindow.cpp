#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include "QColorDialog"

#define pie 3.142

//Environment varaibles
static QImage img(500, 700, QImage::Format_RGB888);
static QColor bgColor(qRgb(0,0,0));
static QColor color(qRgb(230, 230, 230));

//Global declaration
vertex* polygon = new vertex[20];
int verticesCount = 0;
bool drawMode = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    img.fill(bgColor);
    ui->display->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}

// basic UI functions
void MainWindow::on_Color_clicked()
{
    color = QColorDialog::getColor();
}

void MainWindow::clear_screen()
{
    img.fill(bgColor);
    ui->display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_Clear_clicked()
{
    delete[] polygon;
    polygon = new vertex[20];
    verticesCount = 0;
    drawMode = false;
    clear_screen();
}

void MainWindow::on_Draw_clicked()
{
    drawMode = true;
}

//Geometric transformations
void vertex::translate(int tx, int ty)
{
    vertex v(tx, ty);
    *this = *this + v;
}

void vertex::rotate(double A)
{
    vertex temp(*this);

    this->x = (temp.x * cos(A)) - (temp.y * sin(A));
    this->y = (temp.x * sin(A)) + (temp.y * cos(A));

 }

void vertex::rotate(double A, int px, int py)
{
    this->translate(-px, -py);
    this->rotate(A);
    this->translate(px, py);
}

void vertex::scale(float sx, float sy)
{
    vertex v(sx, sy);
    *this = *this * v;
}

// functions for drawing polygon
void MainWindow::dda(float x1,float y1,float x2,float y2){
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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(drawMode){
        if (event->button() == Qt::RightButton){
            dda(polygon[0].x, polygon[0].y, polygon[verticesCount - 1].x, polygon[verticesCount - 1].y);
            drawMode = false;
            return;
        }
        vertex p;
        p.x = event->pos().x();
        p.y = event->pos().y();
        polygon[verticesCount] = p;
        if (verticesCount){
            dda(polygon[verticesCount - 1].x, polygon[verticesCount - 1].y, polygon[verticesCount].x, polygon[verticesCount].y);
        }
        verticesCount++;
    }
}

void MainWindow::draw_polygon()
{
    clear_screen();
    int i=1;
    while(i<verticesCount){
        dda(polygon[i-1].x, polygon[i-1].y, polygon[i].x, polygon[i].y);
        i++;
    }
    dda(polygon[0].x, polygon[0].y, polygon[i-1].x, polygon[i-1].y);
}

//function calls
void MainWindow::on_Translate_clicked()
{
    int tx = ui->tx->toPlainText().toInt();
    int ty = ui->ty->toPlainText().toInt();

    for (int i=0; i<verticesCount; i++){
        polygon[i].translate(tx, ty);
    }
    draw_polygon();
}

void MainWindow::on_Rotate_clicked()
{
    double A = pie*(ui->angle->toPlainText().toDouble())/180;
    int px = ui->px->toPlainText().toInt();
    int py = ui->py->toPlainText().toInt();

    if (px || py){
        for (int i=0; i<verticesCount; i++){
            polygon[i].rotate(A, px, py);
        }
    }
    else {
        for (int i=0; i<verticesCount; i++){
            polygon[i].rotate(A);
        }
    }
    draw_polygon();
}

void MainWindow::on_Scale_clicked()
{
    float sx = ui->sx->toPlainText().toFloat();
    float sy = ui->sy->toPlainText().toFloat();

    for (int i=0; i<verticesCount; i++){
        polygon[i].scale(sx, sy);
    }
    draw_polygon();
}
