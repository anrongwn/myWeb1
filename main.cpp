#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QProcess>
#include <QFile>
#include <QSocketNotifier>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));
    QTextCodec *systemCodec = QTextCodec::codecForLocale();
    qDebug()<<systemCodec->name();

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseOpenGLES);
    QApplication a(argc, argv);

    //修改 QtWebEngineProcess.exe 进程名为 anrongWeb.exe
#ifdef _DEBUG
    QString webengingProcessPath = QCoreApplication::applicationDirPath() + "/" + "anrongWebd.exe";
#else
    QString webengingProcessPath = QCoreApplication::applicationDirPath() + "/" + "anrongWeb.exe";
#endif
    qputenv("QTWEBENGINEPROCESS_PATH", webengingProcessPath.toLocal8Bit());

    /*
    qDebug()<<QApplication::applicationDirPath();
    qDebug()<<QApplication::applicationFilePath();
    */

    MainWindow w;
#ifndef _DEBUG
    w.setWindowFlags(Qt::WindowStaysOnTopHint);//置顶
    w.showFullScreen();
#else
    w.show();
#endif


    /*//windows下无效
    QFile fin;
    if(fin.open(stdin, QIODevice::ReadOnly))
    {
        QSocketNotifier sn(fin.handle(), QSocketNotifier::Read);
    }
    */


    return a.exec();
}
