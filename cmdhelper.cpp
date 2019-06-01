#include "cmdhelper.h"
#include "logger.h"
#include "switchcmd.h"
#include "stringcmd.h"

CMDHelper::CMDHelper(QHash<int, Device*> *devicesMap, QTcpSocket *tcpSocket) : 
    devicesMap_(devicesMap),
    tcpSocket_(tcpSocket)
{
    
}

QHash<int, Device *> *CMDHelper::devicesMap() const
{
    return devicesMap_;
}

void CMDHelper::setDevicesMap(QHash<int, Device *> *devicesMap)
{
    devicesMap_ = devicesMap;
}

QTcpSocket *CMDHelper::tcpSocket() const
{
    return tcpSocket_;
}

void CMDHelper::setTcpSocket(QTcpSocket *tcpSocket)
{
    tcpSocket_ = tcpSocket;
}

void CMDHelper::receiveCMD(const QByteArray &revData)
{
    this->revCmd_.append(revData); // 新数据加入旧数据中
    if (this->revCmd_.isEmpty())
        return;
    
    int start, stop;
    int startDelimiterSize = CMD::startDelimiter().size();
    int stopDelimiterSize = CMD::stopDelimiter().size();
    while (true)
    {
        // 获取命令起始符位置
        if ((start = this->revCmd_.indexOf(CMD::startDelimiter())) == -1)
        {
            this->revCmd_.clear(); // 未找到，说明当前数据无效，清空并退出
            break;
        }
        // 获取命令结束符位置
        if ((stop = this->revCmd_.indexOf(CMD::stopDelimiter(), start + startDelimiterSize)) == -1)
        {
            this->revCmd_ = this->revCmd_.mid(start); // 未找到，说明当前指令未接收完全，从有效位置开始截取，等待下次数据到来
            break;
        }
        
        // 找到了一个命令
        processCMD(this->revCmd_.mid(start + startDelimiterSize, stop - start - startDelimiterSize));
        
        this->revCmd_ = this->revCmd_.mid(stop + stopDelimiterSize);
    }
}

void CMDHelper::clearReceived()
{
    this->revCmd_.clear();
}

void CMDHelper::processCMD(const QString& cmdQString)
{
    int deviceType;
    int deviceId;
    QString left;
    
    // 解析设备类型
    int start = 0;
    int i = 0;
    while (cmdQString[i] != ' ')
        ++i;
    deviceType = cmdQString.mid(start, i - start).toInt();
    ++i;
    
    // 解析设备号
    start = i;
    while (cmdQString[i] != ' ')
        ++i;
    deviceId = cmdQString.mid(start, i - start).toInt();
    ++i;
    
    // 剩余部分
    start = i;
    left = cmdQString.mid(start);
    
    if (this->checkDevicesMap() && this->devicesMap_->contains(deviceId))
    {
        Device *device = (*this->devicesMap_)[deviceId]; // 根据设备号找设备
        switch (static_cast<Device::DeviceType>(deviceType)) // 根据不同设备类型执行不同命令
        {
        case Device::DeviceType::SwitchType:
            SwitchCMD(device, static_cast<Device::SwitchValue>(left.toInt())).execute();
            break;
        case Device::DeviceType::StringType:
            StringCMD(device, left).execute();
            break;
        case Device::DeviceType::KeyType:
            
            break;
        case Device::DeviceType::DigitType:
            
            break;
        }
    }
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

bool CMDHelper::checkDevicesMap() const
{
    if (this->devicesMap_ == nullptr || this->devicesMap_->empty())
    {
        Logger::getLogger() << "Devices map is null or empty";
        return false;
    }
    return true;
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


