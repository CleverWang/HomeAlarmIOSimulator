#ifndef SWITCHCMD_H
#define SWITCHCMD_H

#include "cmd.h"

// 开关型设备命令
class SwitchCMD : public CMD
{
public:
    SwitchCMD(Device * device, Device::SwitchValue switchValue);
    
    QString toQStringCMD() const override;
    void execute() override;
protected:
    // 开关型设备的值
    Device::SwitchValue switchValue_;
};

#endif // SWITCHCMD_H
