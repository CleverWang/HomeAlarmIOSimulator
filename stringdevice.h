#ifndef STRINGDEVICE_H
#define STRINGDEVICE_H

#include "device.h"

// 字符串型设备
class StringDevice : public Device
{
public:
    StringDevice(DeviceId deviceId, QObject *device);
    
    void executeCMD(const QString &string) override;
};

#endif // STRINGDEVICE_H
