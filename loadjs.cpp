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

    QString path(R"(D:\MyTest\2019_Qt\myWeb1\)");//当前目录
    path=R"(:/)";                               //QRC 中
    path+=fn;
    QFile jsfile(path);
    if (jsfile.open(QIODevice::ReadOnly)){
        js = jsfile.readAll().constData();
    }

    return js ;
}

QString loadJS::addScript(const QString &fn)
{

    QString js;//("(function(){\r\n");
    js+="var ohead= document.getElementsByTagName('body')[0];\r\nvar oscript= document.createElement('script');\r\noscript.type= 'text/javascript';\r\n";
    js+="oscript.text='";

    QString path(R"(D:\MyTest\2019_Qt\myWeb1\)");
    path=R"(:/)";
    path+=fn;
    QFile jsfile(path);
    QString text;
    //text+="var content;function fn(){content=\"hello,wangjr\";/*sdfadf*/;};fn();document.write(content);";
    /*
    text+="var ohead= document.getElementsByTagName('body')[0];var oscript= document.createElement('script');\
        oscript.type= 'text/javascript';oscript.text='var context;\
        function init(){new QWebChannel(qt.webChannelTransport, function(channel){context = channel.objects.context;});\
        document.getElementById(\"bn1\").onclick=onBtnSendMsg;};function onBtnSendMsg(){var cmd = document.getElementById(\"in1\").value;sendMessage(cmd);};\
        function sendMessage(msg){context.onMsg(1, msg);};function recvMessage(msg){var obj = document.getElementById(\"in1\");obj.value=msg;return \"index.html--recvMessage\";};\
        init();';\
        ohead.appendChild(oscript);";
        */


    /*js文件中注释不能用//，字符串使用""，每个语名结束要有;(含}，最后行不能有换行)*/
    if (jsfile.open(QIODevice::ReadOnly)){

        text+= jsfile.readAll().constData();

        text.replace("\r\n", "");
        //qDebug()<< "===loadJS::addScript open" << path << text;
    }
    else{
         qDebug()<< "===loadJS::addScript open" << path << " failed.";
    }


    js+=text;
    js+="';\r\nohead.appendChild(oscript);\r\n";
    //js+="\r\nohead.appendChild(oscript);\r\n";
    //js+=QString("})();\r\n");


    /*
    QFile inf(R"(D:\MyTest\2019_Qt\myWeb1\temp.js)");
    if (inf.open(QIODevice::WriteOnly|QIODevice::Truncate))
    {
        inf.write(js.toUtf8());
        inf.flush();
        inf.close();
    }
    qDebug()<< "===" << QTime::currentTime().toString("hh:mm:ss.zzz")<<" loadJS::addScript result: " << js;
    */

    return js ;
}

int loadJS::synRun(QWebEnginePage *page, const QString &js, const int ms)
{
    int r = 0;
    QEventLoop loop;
    QObject::connect(this, &loadJS::jsCompleted, &loop, &QEventLoop::quit);
    page->runJavaScript(js, [&](const QVariant &v){
        Q_UNUSED(v);
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
