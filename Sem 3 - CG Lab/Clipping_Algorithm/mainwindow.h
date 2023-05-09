#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class point
{
public:
    float x;
    float y;
    int outcode = 0;
    friend class MainWindow;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void dda(float x1,float y1,float x2,float y2, uint value);
    void setOutcode(point &p);
    int checkOutcode(point p1, point p2);
    void clipline_oneinside(point &p1, point &p2);
    void draw_window();

private slots:
    void on_window_clicked();

    void on_color_clicked();

    void on_draw_line_clicked();

    void on_clip_line_clicked();

    void on_window_color_clicked();

protected slots:
    void mousePressEvent(QMouseEvent *event);

};
#endif // MAINWINDOW_H
