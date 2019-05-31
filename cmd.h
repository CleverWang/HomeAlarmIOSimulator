#ifndef CMD_H
#define CMD_H

#include <limits>

#include <QString>

#include "device.h"

class CMD
{
public:
    static QString startDelimiter();
    static void setStartDelimiter(const QString &startDelimiter);
    
    static QString stopDelimiter();
    static void setStopDelimiter(const QString &stopDelimiter);
    
    // KeyType型命令
    CMD(Device::DeviceType deviceType, Device::DeviceId deviceId);
    // SwitchType型命令
    CMD(Device::DeviceType deviceType, Device::DeviceId deviceId, Device::SwitchValue switchValue);
    // DigitType型命令
    CMD(Device::DeviceType deviceType, Device::DeviceId deviceId, double digitValue);
    // StringType型命令
    CMD(Device::DeviceType deviceType, Device::DeviceId deviceId, const QString &stringValue);
    
    Device::DeviceType deviceType() const;
    void setDeviceType(const Device::DeviceType &deviceType);
    
    Device::DeviceId deviceId() const;
    void setDeviceId(const Device::DeviceId &deviceId);
    
    Device::SwitchValue switchValue() const;
    void setSwitchValue(const Device::SwitchValue &switchValue);
    
    double digitValue() const;
    void setDigitValue(double digitValue);
    
    QString stringValue() const;
    void setStringValue(const QString &stringValue);
    
    QString toString() const;
    
private:
    constexpr static double UnknownDigitValue = std::numeric_limits<double>::max();
    
    // 起始分隔符
    static QString startDelimiter_;
    // 结束分隔符
    static QString stopDelimiter_;
    
    // 设备类型
    Device::DeviceType deviceType_;
    // 设备ID
    Device::DeviceId deviceId_;
    // 开关型设备的值
    Device::SwitchValue switchValue_;
    // 数值型设备的值
    double digitValue_;
    // 字符串型设备的值
    QString stringValue_;
};

#endif // CMD_H
