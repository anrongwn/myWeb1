#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineSettings>
#include <QWebEngineProfile>
#include <QWebEngineCookieStore>
#include <QNetworkCookie>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <QTime>
#include <QThread>
#include "loadjs.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    webView_ = new CMyWebView(this);
    //ui->verticalLayout->addWidget(webView_);

    QWebEngineSettings * set = webView_->settings();
    set->setAttribute(QWebEngineSettings::PluginsEnabled, true);

    webView_->setAttribute(Qt::WA_DeleteOnClose, true);
    //webView_->load(QUrl("index.html"));
    //webView_->setUrl(QUrl("qrc:/index.html"));

    jsContext_ = new JsContext(this);
    channel_ = new QWebChannel(this);
    channel_->registerObject("context", jsContext_);
    webView_->page()->setWebChannel(channel_);
    QObject::connect(jsContext_, &JsContext::recvMsg, this, &MainWindow::onPageMsg);
    //QObject::connect(webView_, &CMyWebView::loadFinished, this, &MainWindow::onloadFinished);
    QObject::connect(webView_->page(), &QWebEnginePage::loadFinished, this, &MainWindow::onloadFinished);
    QObject::connect(webView_->page(), &QWebEnginePage::loadStarted, this, &MainWindow::onloadStarted);

    QString urlName("D:\\MyTest\\2019_Qt\\myWeb1\\index.html");
    QUrl url = QUrl::fromUserInput(urlName);

    webView_->load(url);
    //webView_->syncload(url);

    QWebEngineProfile *profile = webView_->page()->profile();
    QWebEngineCookieStore* cookie = profile->cookieStore();

    QNetworkCookie cookieinfo("amount", "1000");
    cookie->setCookie(cookieinfo, url);


    webView_->show();
}

MainWindow::~MainWindow()
{
    jsContext_->deleteLater();
    channel_->deleteLater();
    //webView_->disconnect();
    webView_->deleteLater();

    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    webView_->resize(this->size());
}

void MainWindow::onPageMsg(int noteid, const QString &msg)
{
    qDebug()<<"======" << QTime::currentTime().toString("hh:mm:ss.zzz") <<QString(" Received  webpage  message: '%1'").arg(msg);

    QString urlName, echo;

    switch (noteid){
    case 1:
        echo+=msg;
        echo+=" ,Withdrawals success!";
        urlName+=R"(D:\MyTest\2019_Qt\myWeb1\page2.html)";


        break;
    case 2:
        echo+="Please enter the withdrawal amount:";
        urlName+=R"(D:\MyTest\2019_Qt\myWeb1\index.html)";

        break;
    }
    QUrl url = QUrl::fromUserInput(urlName);

    QWebEngineProfile *profile = webView_->page()->profile();
    QWebEngineCookieStore* cookie = profile->cookieStore();

    QNetworkCookie cookieinfo("amount", msg.toLocal8Bit());
    cookie->setCookie(cookieinfo, url);



    qDebug()<<"=====" << QTime::currentTime().toString("hh:mm:ss.zzz") <<" webView_->load(" << url << "), begining.";

    webView_->load(url);

    //webView_->syncload(url);
    qDebug()<<"=====" << QTime::currentTime().toString("hh:mm:ss.zzz") <<" webView_->load(" << url << "), end.";

    //jsContext_->sendMsg(webView_->page(), echo);

}

void MainWindow::onloadFinished(bool ok)
{
    if (!ok) return;

    QUrl url = this->webView_->page()->url();
    QString fn = url.toLocalFile();

    qDebug()<<"====="<< QTime::currentTime().toString("hh:mm:ss.zzz ") <<url<<" loadFinished.";

    QString param("2000");

    if (fn==R"(D:/MyTest/2019_Qt/myWeb1/index.html)"){
        loadJS load;
        QString js = load.addScript("test1.js");
        load.asynRun(this->webView_->page(), js);

        //
        QThread::msleep(10);
    }


    jsContext_->sendMsg(webView_->page(), param);
    qDebug()<<"=====" << QTime::currentTime().toString("hh:mm:ss.zzz") << " jsContext_->sendMsg completed.";

}

void MainWindow::onloadStarted()
{
    QUrl url = this->webView_->page()->url();
    qDebug()<<"====="<< QTime::currentTime().toString("hh:mm:ss.zzz ") <<url<<" onloadStarted.";


    /*
    loadJS load;
    QString js = load.addScript("test1.js");
    load.asynRun(this->webView_->page(), js);
    */

}

/*
void MainWindow::on_pushButton_3_clicked()
{
    webView_->forward();
}

void MainWindow::on_pushButton_2_clicked()
{
    webView_->back();
}

void MainWindow::on_pushButton_clicked()
{
    webView_->reload();
}
*/
