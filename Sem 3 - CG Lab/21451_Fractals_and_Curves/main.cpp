#include "koch_curve.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    koch_curve w;
    w.show();
    return a.exec();
}
