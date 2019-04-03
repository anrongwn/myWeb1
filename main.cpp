#include "mainwindow.h"
#include <QApplication>
#include <QDebug>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);

    /*
    qDebug()<<QApplication::applicationDirPath();
    qDebug()<<QApplication::applicationFilePath();
    */

    MainWindow w;
#ifndef _DEBUG
    w.setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
#endif
    w.show();
    //w.showFullScreen();

    return a.exec();
}
