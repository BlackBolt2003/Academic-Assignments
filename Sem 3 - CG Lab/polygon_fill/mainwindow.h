#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Delay{
public:
        void delay(int millisecondsToWait);
};

class MainWindow : public QMainWindow,Delay
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    //void seedFill(int x,int y,QRgb);
    void dda(float x1,float y1,float x2,float y2);
    void bresenhem(int x1,int y1,int x2,int y2);
//    void delay(int n);
    void scanLineFill();


private:
    Ui::MainWindow *ui;
    int a[10];
    int b[10];
    int ver;
    bool start;
    float dx,dy,xi[100];
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);

};
#endif // MAINWINDOW_H
