#ifndef CMDHELPER_H
#define CMDHELPER_H

#include <QTcpSocket>
#include <QObject>

#include "cmd.h"

class CMDHelper: public QObject
{
    Q_OBJECT
public:
    CMDHelper(QTcpSocket *tcpSocket = nullptr);
    
    QTcpSocket *tcpSocket() const;
    void setTcpSocket(QTcpSocket *tcpSocket);
    
private:
    bool checkSocket() const;
    
    QTcpSocket *tcpSocket_; // socket连接
    
public slots:
    // 槽，用于接受各种类型设备发送的命令，然后通过socket发送出去
    bool writeCMD(const QString &cmd);
};

#endif // CMDHELPER_H
