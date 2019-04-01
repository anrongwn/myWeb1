#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "cmywebview.h"
#include <QWebChannel>
#include "jscontext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
    void onPageMsg(int nodeid, const QString& msg);

    void onloadFinished(bool ok);
    /*
private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    */

private:
    Ui::MainWindow *ui;

    CMyWebView * webView_=nullptr;
    JsContext * jsContext_=nullptr;
    QWebChannel * channel_=nullptr;
};

#endif // MAINWINDOW_H
