#include "zhuanhuan.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    zhuanhuan w;
    w.show();

    return a.exec();
}
