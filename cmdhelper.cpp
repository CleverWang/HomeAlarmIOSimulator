#include "cmdhelper.h"
#include "logger.h"

CMDHelper::CMDHelper(QTcpSocket *tcpSocket) : tcpSocket_(tcpSocket)
{
    
}

QTcpSocket *CMDHelper::tcpSocket() const
{
    return tcpSocket_;
}

void CMDHelper::setTcpSocket(QTcpSocket *tcpSocket)
{
    tcpSocket_ = tcpSocket;
}

bool CMDHelper::writeCMD(const QString &cmd)
{
    if (checkSocket() == true)
    {
        if (this->tcpSocket_->write(cmd.toStdString().c_str()) != -1)
        {
            Logger::getLogger() << "write " + cmd + " successed";
            return true;
        }
    }
    Logger::getLogger() << "write " + cmd + " failed";
    return false;
}

bool CMDHelper::checkSocket() const
{
    if (this->tcpSocket_ == nullptr || this->tcpSocket_->isValid() == false)
    {
        Logger::getLogger() << "TCP socket is null or not valid";
        return false;
    }
    return true;
}
