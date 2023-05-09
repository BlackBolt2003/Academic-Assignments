#ifndef KOCH_CURVE_H
#define KOCH_CURVE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class koch_curve; }
QT_END_NAMESPACE

class koch_curve : public QMainWindow
{
    Q_OBJECT

public:
    koch_curve(QWidget *parent = nullptr);
    ~koch_curve();
    void dda(float x1, float y1, float x2, float y2);
    void drawCurve(int it, int x1, int y1, int x2, int y2);

private slots:
    void on_create_clicked();

private:
    Ui::koch_curve *ui;
};

#endif // KOCH_CURVE_H
