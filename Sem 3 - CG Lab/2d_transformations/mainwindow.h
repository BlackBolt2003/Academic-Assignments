#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void dda(float x1, float y1, float x2, float y2);
    void draw_polygon();
    void clear_screen();

    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_Color_clicked();
    void on_Clear_clicked();
    void on_Draw_clicked();

    void on_Translate_clicked();

    void on_Rotate_clicked();

    void on_Scale_clicked();

private:
    Ui::MainWindow *ui;
};

class vertex
{
public:
    int x;
    int y;
    vertex(){
        x = 0;
        y = 0;
    }

    vertex(int x, int y){
        this->x = x;
        this->y = y;
    }

    vertex(vertex &v){
        this->x = v.x;
        this->y = v.y;
    }

    vertex operator + (vertex t){
        this->x += t.x;
        this->y += t.y;
        return *this;
    }

    vertex operator - (vertex t){
        this->x -= t.x;
        this->y -= t.y;
        return *this;
    }

    vertex operator *(vertex s){
        this->x *= s.x;
        this->y *= s.y;
        return *this;
    }

    void translate(int tx, int ty);
    void rotate(double A);
    void rotate(double A, int p1, int p2);
    void scale(float sx, float sy);
};

#endif // MAINWINDOW_H
