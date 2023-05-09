#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QColorDialog"

static QImage img(500, 500, QImage::Format_RGB888);
static QRgb bgColor(qRgb(0, 0, 0));
static QRgb color(qRgb(255, 0, 0));
static QRgb windowColor(qRgb(255, 255, 255));

int countPoints = 0;
bool drawline = false;
bool setWindow = false;
point *arr = new point[20];

static float wx1, wx2, wy1, wy2;
// 1 = min value, 2 = max value, for wx and wy

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
    delete[] arr;
    arr = NULL;
    delete ui;
}

void MainWindow::on_window_clicked()
{
    // get diagonal points of clipping window
    wx1 = ui->x1->toPlainText().toInt();
    wy1 = ui->y1->toPlainText().toInt();
    wx2 = ui->x2->toPlainText().toInt();
    wy2 = ui->y2->toPlainText().toInt();

    // draw edges of clipping window
    draw_window();

    setWindow = true;
}

void MainWindow::on_color_clicked()
{
    color = QColorDialog::getColor().rgb();
}

void MainWindow::on_window_color_clicked()
{
    windowColor = QColorDialog::getColor().rgb();
}

void MainWindow::draw_window()
{
    dda(wx1, wy1, wx2, wy1, windowColor);
    dda(wx1, wy1, wx1, wy2, windowColor);
    dda(wx2, wy1, wx2, wy2, windowColor);
    dda(wx1, wy2, wx2, wy2, windowColor);

    ui->display->setPixmap(QPixmap::fromImage(img));
}

void MainWindow::on_draw_line_clicked()
{
    drawline = true;
}

void MainWindow::setOutcode(point &p)
{
    (p.y > wy2)?(p.outcode += 8):(p.outcode += 0);
    (p.y < wy1)?(p.outcode += 4):(p.outcode += 0);
    (p.x > wx2)?(p.outcode += 2):(p.outcode += 0);
    (p.x < wx1)?(p.outcode += 1):(p.outcode += 0);
}

int MainWindow::checkOutcode(point p1, point p2)
{
    if (!(p1.outcode | p2.outcode)){
        // completely inside
        return 1;
    }
    else if (p1.outcode & p2.outcode){
        // completely outside
        return 0;
    }
    // else partially inside
    return 2;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (drawline && setWindow){
        point p;
        p.x = event->pos().x();
        p.y = event->pos().y();
        setOutcode(p);
        arr[countPoints] = p;
        if (countPoints % 2 != 0){
            dda(arr[countPoints-1].x, arr[countPoints-1].y, arr[countPoints].x, arr[countPoints].y, color);
            ui->display->setPixmap(QPixmap::fromImage(img));
        }
        countPoints++;
    }
}

void MainWindow::dda(float x1,float y1,float x2,float y2, uint value){
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

void MainWindow::on_clip_line_clicked()
{
    int i = 0;
    while (i <= countPoints){
        int check = checkOutcode(arr[i], arr[i+1]);
        if (check == 0){
            // completely outside, set endpoints as '-1'
            arr[i].x = arr[i].y = arr[i+1].x = arr[i+1].y -1;
        }

        else if (check == 2){
            // line partially inside
            // formulae :
            // y = y0 + m * (x - x0)
            // x = x0 + (1/m) * (y - y0)

            // calculate slope of line
            float m = (arr[i+1].y - arr[i].y) / (arr[i+1].x - arr[i].x);

            // at least one endpoint outside clip-window, select it
            point outPoint = (arr[i].outcode > arr[i+1].outcode) ? (arr[i]) : (arr[i+1]);
            point inPoint = (arr[i].outcode < arr[i+1].outcode) ? (arr[i]) : (arr[i+1]);

            switch(outPoint.outcode){
            case 1 : // x is fixed as wx1, y calculated accordingly
                outPoint.y = inPoint.y + (m * (wx1 - inPoint.x));
                outPoint.x = wx1;
                break;

            case 2 : // x is fixed as wx2, y calculated accordingly
                outPoint.y = inPoint.y + (m * (wx2 - inPoint.x));
                outPoint.x = wx2;
                break;

            case 4 : // y is fixed as wy1, x calculated accordingly
                outPoint.x = inPoint.x + ((1/m) * (wy1 - inPoint.y));
                outPoint.y = wy1;
                break;

            case 8 : // y is fixed as wy2, x calculated accordingly
                outPoint.x = inPoint.x + ((1/m) * (wy2 - inPoint.y));
                outPoint.y = wy2;
                break;
            }

            if (arr[i].outcode > arr[i+1].outcode){
                arr[i].x = outPoint.x;
                arr[i].y = outPoint.y;
            } else {
                arr[i+1].x = outPoint.x;
                arr[i+1].y = outPoint.y;
            }
        }
        i += 2;
    }

    // refresh display area
    for (int i=0; i<500; i++){
        for (int j=0; j<500; j++){
            img.setPixel(i, j, bgColor);
        }
    }
    ui->display->setPixmap(QPixmap::fromImage(img));

    // create window again
    draw_window();

    // draw clipped lines
    i = 0;
    while (i <= countPoints){
        if (arr[i].x != -1) {
            dda(arr[i].x, arr[i].y, arr[i+1].x, arr[i+1].y, color);
        }
        i+=2;
    }

    ui->display->setPixmap(QPixmap::fromImage(img));
}

