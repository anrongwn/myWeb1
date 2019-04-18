#ifndef CMYWEBVIEW_H
#define CMYWEBVIEW_H
#include <QWidget>
#include <QWebEngineView>
#include "canwebpage.h"


class CMyWebView : public QWebEngineView
{
    Q_OBJECT

public:
    explicit CMyWebView(QWidget * parent=nullptr);
    ~CMyWebView();

Q_SIGNALS:
    void syncloaded();

public:
    void syncload(const QUrl &url);

public slots:
    void onlinkHovered(const QString &url);
    void requestLoadPage(const QUrl &url);
    void onloadFinished(bool ok);

protected:
    QWebEngineView * createWindow(QWebEnginePage::WebWindowType type);

private:
    QUrl url_;

};

#endif // CMYWEBVIEW_H
