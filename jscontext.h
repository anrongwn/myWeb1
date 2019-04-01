#ifndef JSCONTEXT_H
#define JSCONTEXT_H

#include <QObject>
#include <QString>
#include <QWebEnginePage>
#include <QVariant>

class JsContext : public QObject
{
    Q_OBJECT
public:
    explicit JsContext(QObject* parent=nullptr);
    ~JsContext();

signals:
    void recvMsg(int nodeid, const QString& msg);
    void jsCompleted();

public:
    void sendMsg(QWebEnginePage* page, QString& msg);
    QVariant execJs(QWebEnginePage* page, const QString& js);

public slots:
    void onMsg(int nodeid, const QString& msg);

};

#endif // JSCONTEXT_H
