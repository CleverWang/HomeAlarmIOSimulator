#ifndef CMDHELPER_H
#define CMDHELPER_H

#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QHash>

#include "cmd.h"

class CMDHelper: public QObject
{
    Q_OBJECT
public:
    CMDHelper(QHash<int, Device*> *devicesMap = nullptr, QTcpSocket *tcpSocket = nullptr);
    
    QHash<int, Device *> *devicesMap() const;
    void setDevicesMap(QHash<int, Device *> *devicesMap);
    QTcpSocket *tcpSocket() const;
    void setTcpSocket(QTcpSocket *tcpSocket);
    
    void receiveCMD(const QByteArray &revData);
    void clearReceived();
    
private:
    bool checkDevicesMap() const;
    bool checkSocket() const;
    void processCMD(const QString& cmdQString);
    
    QHash<int, Device*> *devicesMap_;
    QTcpSocket *tcpSocket_; // socket连接
    
    QString revCmd_;
    
public slots:
    // 槽，用于接受各种类型设备发送的命令，然后通过socket发送出去
    bool writeCMD(const QString &cmd);
};

#endif // CMDHELPER_H
