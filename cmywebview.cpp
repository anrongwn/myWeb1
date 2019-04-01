#include "cmywebview.h"
#include <QWebEngineSettings>
#include <QDebug>
#include <QEventLoop>
#include <QTimer>


CMyWebView::CMyWebView(QWidget *parent) : QWebEngineView(parent)
{
    connect(this->page(), &QWebEnginePage::linkHovered, \
            this, &CMyWebView::onlinkHovered);


    /*
    connect(this->page(), &QWebEnginePage::loadFinished, \
            this, &CMyWebView::onloadFinished);
    */

}

CMyWebView::~CMyWebView()
{
    this->deleteLater();
}

void CMyWebView::syncload(const QUrl &url)
{
    QEventLoop loop;
    QObject::connect(this, &CMyWebView::syncloaded, &loop, &QEventLoop::quit);

    // Schedule the slot to run in 0 seconds but not right now
    //QTimer::singleShot(0, this, SLOT(requestLoadPage(url)));
    QTimer::singleShot(0, [=](){
        requestLoadPage(url);
    });
    //

    loop.wakeUp();
    // The event loop would block until the lambda receiving the HTML is executed
    loop.exec();

}

void CMyWebView::onlinkHovered(const QString &url)
{
    url_=url;
}

void CMyWebView::requestLoadPage(const QUrl &url)
{
    this->load(url);
}

void CMyWebView::onloadFinished(bool ok)
{
    Q_UNUSED(ok);
    emit syncloaded();
}

QWebEngineView *CMyWebView::createWindow(QWebEnginePage::WebWindowType type)
{
    Q_UNUSED(type);

    this->load(url_);

    return this;
    //return nullptr;
}
