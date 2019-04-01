#include "jscontext.h"
#include <QEventLoop>
#include <QTimer>


#include <QTime>
JsContext::~JsContext()
{

}

void JsContext::sendMsg(QWebEnginePage *page, QString &msg)
{
    QString js=QString("recvMessage('%1');").arg(msg);

    //同步
    QEventLoop loop;
    QObject::connect(this, &JsContext::jsCompleted, &loop, &QEventLoop::quit);

    //QString result;
    page->runJavaScript(js, [&](const QVariant &v){
        //result=v.toString();

        //loop.exit();

        emit jsCompleted();

        qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" page->runJavaScript result: " << v.toString();

    });

    //必须调用，否则无法及时唤醒事件处理，导致runJavaScript回调延时。
    loop.wakeUp();

    loop.exec(QEventLoop::AllEvents);

    qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<" sendMsg, loop.exec() exit.";

    /*//异步
    page->runJavaScript(js);
    */

}

QVariant JsContext::execJs(QWebEnginePage *page, const QString &js)
{
    //同步
    QEventLoop loop;
    QObject::connect(this, &JsContext::jsCompleted, &loop, &QEventLoop::quit);

    QVariant result;
    page->runJavaScript(js, [&](const QVariant &v){

        result=v;
        emit jsCompleted();

        qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" page->runJavaScript result: " << result;

    });

    //必须调用，否则无法及时唤醒事件处理，导致runJavaScript回调延时。
    loop.wakeUp();

    loop.exec(QEventLoop::AllEvents);

    qDebug()<<"==="<< QTime::currentTime().toString("hh:mm:ss.zzz")<<" execJs, loop.exec() exit.";

    return result;
}

void JsContext::onMsg(int nodeid, const QString &msg)
{
    emit recvMsg(nodeid, msg);
}

JsContext::JsContext(QObject *parent) : QObject(parent)
{

}
