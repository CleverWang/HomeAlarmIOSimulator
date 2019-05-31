#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

#include "cmdhelper.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = nullptr, quint16 port = 1314);
    ~Widget();
    
private:
    void closeConnection();
    void onNewConnection();
    void onReadyRead();
    void setupUISignalSlot();
    
    Ui::Widget *ui;
    
    QTcpServer *tcpServer_;
    QTcpSocket *tcpSocket_;
    
    quint16 port_;
    
    CMDHelper *cmdHelper;
};

#endif // WIDGET_H
