#ifndef DIGITCMD_H
#define DIGITCMD_H

#include "cmd.h"

// 数字型设备命令
class DigitCMD : public CMD
{
public:
    DigitCMD(const Device * const device, double digitValue);
    
    QString toQStringCMD() const override;
    
protected:
    // 数值型设备的值
    double digitValue_;
};

#endif // DIGITCMD_H
