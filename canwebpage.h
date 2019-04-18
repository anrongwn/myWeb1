#ifndef CANWEBPAGE_H
#define CANWEBPAGE_H

#include <QObject>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineScript>
#include <QWebEngineSettings>
#include <QWebChannel>

class CAnWebPage : public QWebEnginePage
{
    Q_OBJECT
public:
    explicit CAnWebPage(QObject *parent = Q_NULLPTR);
    ~CAnWebPage();

public:
    static QWebEngineProfile * createWebEngineProfile(QObject * parent);
};

#endif // CANWEBPAGE_H
