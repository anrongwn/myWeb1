#include "canwebpage.h"

CAnWebPage::CAnWebPage(QObject *parent):QWebEnginePage(parent)
{

}

CAnWebPage::~CAnWebPage()
{

}

QWebEngineProfile *CAnWebPage::createWebEngineProfile(QObject *parent)
{
    Q_UNUSED(parent);
    return nullptr;

}
