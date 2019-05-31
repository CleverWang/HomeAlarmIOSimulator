#ifndef CMDHELPER_H
#define CMDHELPER_H

#include <QTcpSocket>

#include "cmd.h"

class CMDHelper
{
public:
    CMDHelper(QTcpSocket *tcpSocket = nullptr);
    
    QTcpSocket *tcpSocket() const;
    void setTcpSocket(QTcpSocket *tcpSocket);
    
    bool writeCMD(const CMD &cmd);
    
private:
    bool checkSocket() const;
    
    QTcpSocket *tcpSocket_;
};

#endif // CMDHELPER_H
