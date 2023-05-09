#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMouseEvent>
#include<QtDebug>
#include"QColorDialog"
#include<QTime>
#include<iostream>
using namespace std;
static QImage img(500,500,QImage::Format_RGB888);
static QColor color;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ver = 0;
    start = true;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dda(float x1,float y1,float x2,float y2){
    float x,y,dx,dy,l,i=1;
    l = abs(x2-x1)>abs(y2-y1)?abs(x2-x1):abs(y2-y1);
    dx = (x2-x1)/l;
    dy = (y2-y1)/l;
    x = x1+0.5f;
    y = y1+0.5f;
    do{
        img.setPixel(static_cast<int>(x),static_cast<int>(y),color.rgb());
        x = x+dx;
        y = y+dy;
        i++;
    } while(i<=l);
    ui->label->setPixmap(QPixmap::fromImage(img));

}
int sign(int n){
    if(n<0)
        return -1;
    else return 1;
}
void MainWindow::bresenhem(int x1,int y1,int x2,int y2){
    int x,y;
    x = x1;
    y = y1;
    int dx,dy,p;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    int i = 0;
    if(dx>=dy){
        p = 2*dy - dx;
        while(i<dx){
            img.setPixel(x,y,color.rgb());
            if(p>0){
                p+=2*dy-2*dx;

                y+= sign(y2-y1);
            }
            else if (p<0){
                p+=2*dy;

            }
            x+=sign(x2-x1);
            i++;
        }

    }
    else{
        p = 2*dx - dy;
        while(i<dy){
            img.setPixel(x,y,color.rgb());
            if(p>0){
                p+=2*dx-2*dy;
                x+=sign(x2-x1);
            }
            else if (p<0){
                p+=2*dx;

            }
            y+=sign(y2-y1);
            i++;
        }
    }

    ui->label->setPixmap(QPixmap::fromImage(img));
}


void MainWindow::on_pushButton_clicked(){
    color = QColorDialog::getColor();
}
void MainWindow::mousePressEvent(QMouseEvent *ev){
    if(start){
        int p = ev->pos().x();
        int q = ev->pos().y();
        a[ver]=p;
        b[ver]=q;
        if(ev->button()==Qt::RightButton){
            dda(a[0],b[0],a[ver-1],b[ver-1]);
            start = false;
        }else{
            if(ver>0){
                dda(a[ver],b[ver],a[ver-1],b[ver-1]);
            }
        }
        ver++;

    }
}

void MainWindow::scanLineFill()
{
    int yMin = 10000000,yMax = 0,temp;
    float slope[100];
    //find yMax and yMin
    for(int i =0;i<ver;i++){
        if(b[i]>yMax)
            yMax = b[i];
        if(b[i]<yMin)
            yMin = b[i];
    }
    a[ver] = a[0];
    b[ver] = b[0];
    for(int i =0;i<ver;i++){
        dx = a[i+1]-a[i];
        dy = b[i+1]-b[i];
        if(dx==0.0)slope[i]=0.0;
        if(dy==0.0)slope[i]=1.0;
        if(dx!=0.0 && dy!=0.0){
            slope[i]=(float)dx/(float)dy;
        }
    }
    int k;
    for(int j=yMin;j<yMax;j++)
        {

            k=0;

            for(int i=0;i<ver;i++){

                if(((b[i]<=j) && (b[i+1]>j)) || ((b[i]>j) && (b[i+1]<=j))){

                    xi[k]=(int)(a[i]+(slope[i]*(j-b[i])));
                    k++;
                }
            }
            for(int m=0;m<k-1;m++){

                for(int i=0;i<k-m-1;i++){

                    if(xi[i]>xi[i+1]){

                        temp=xi[i];

                        xi[i]=xi[i+1];

                        xi[i+1]=temp;

                    }

                }
            }
                for(int i=0;i<k;i+=2){
                    bresenhem(xi[i],j,xi[i+1]+1,j);
                    delay(5);
                }
        }
}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *event){

    scanLineFill();
}


void Delay::delay(int millisecondsToWait)
{
    QTime dieTime = QTime::currentTime().addMSecs(millisecondsToWait);
    while (QTime::currentTime() < dieTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}
