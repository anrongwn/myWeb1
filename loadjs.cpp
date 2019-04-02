#include "loadjs.h"
#include <QString>
#include <QFile>
#include <QTextCodec>
#include <QDebug>
#include <QThread>



loadJS::loadJS(QObject *parent) : QObject(parent)
{

}

QString loadJS::addScriptSrc(const QString &fn)
{
    QString js;

    QString path(R"(D:\MyTest\2019_Qt\myWeb1\)");
    path+=fn;
    QFile jsfile(path);
    if (jsfile.open(QIODevice::ReadOnly)){
        js = jsfile.readAll().constData();
    }

    return js ;
}

QString loadJS::addScript(const QString &fn)
{
    QString js("<script>\r\n");

    QString path(R"(D:\MyTest\2019_Qt\myWeb1\)");
    path+=fn;
    QFile jsfile(path);
    if (jsfile.open(QIODevice::ReadOnly)){
        js += jsfile.readAll().constData();
    }
    js+=QString("\r\n</script>");

    return js ;
}

int loadJS::synRun(QWebEnginePage *page, const QString &js, const int ms)
{
    int r = 0;
    QEventLoop loop;
    QObject::connect(this, &loadJS::jsCompleted, &loop, &QEventLoop::quit);
    page->runJavaScript(js, [&](const QVariant &v){
        //result=v.toString();

        //loop.exit();

        emit jsCompleted();

        //qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" page->runJavaScript result: " << v.toString();

    });

    //必须调用，否则无法及时唤醒事件处理，导致runJavaScript回调延时。
    loop.wakeUp();

    loop.exec(QEventLoop::AllEvents);

    QThread::msleep(ms);

    qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<" asynRun, loop.exec() exit.";


    return r;
}

int loadJS::synRun(QWebEnginePage* page, const QString &jsContent){
    int r = 0;


    QString js=QString("document.write('%1');").arg(jsContent);
    QEventLoop loop;
    QObject::connect(this, &loadJS::jsCompleted, &loop, &QEventLoop::quit);
    page->runJavaScript(js, [&](const QVariant &v){
        //result=v.toString();

        //loop.exit();

        emit jsCompleted();

        qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" page->runJavaScript result: " << v.toString();

    });

    //必须调用，否则无法及时唤醒事件处理，导致runJavaScript回调延时。
    loop.wakeUp();

    loop.exec(QEventLoop::AllEvents);


    qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<" asynRun, loop.exec() exit.";



    return r;
}
