#include "startwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <iostream>
void test(){std::cout << "ssss";}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto f = QApplication::desktop();
    StartWindow w(0,f->width(),f->height());
    w.show();

    return a.exec();
}
