#ifndef LOADJS_H
#define LOADJS_H

#include <QObject>
#include <QEventLoop>
#include <QWebEnginePage>

class loadJS : public QObject
{
    Q_OBJECT
public:
    explicit loadJS(QObject *parent = nullptr);

signals:
    void jsCompleted();

public slots:

public:
    QString addScriptSrc(const QString &fn);
    QString addScript(const QString &fn);


    int synRun(QWebEnginePage* page, const QString &js, const int ms);
    int synRun(QWebEnginePage* page, const QString &jsContent);
};

#endif // LOADJS_H
