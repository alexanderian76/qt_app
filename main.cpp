#include <QApplication>
#include "mainwindow.h"



int main(int argc, char *argv[ ])
{
    QApplication app(argc, argv);
    MainWindow w;
    w.resize(600,480);
   // w.showFullScreen();
    w.show();
    return app.exec();
}
