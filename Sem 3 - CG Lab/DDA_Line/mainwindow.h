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
    void dda_algo(int x1, int y1, int x2, int y2);
    void bresenham_circle(int xc, int yc, int r);
    void midpoint_circle(int xc, int yc, int r);

private slots:
    void on_DDA_line_clicked();
    void on_B_Circle_clicked();
    void on_M_Circle_clicked();

    void on_create_1_clicked();

    void on_clear_clicked();

    void on_create_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
