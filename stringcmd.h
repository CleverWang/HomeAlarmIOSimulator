#ifndef STRINGCMD_H
#define STRINGCMD_H

#include "cmd.h"

// 字符串型设备命令
class StringCMD : public CMD
{
public:
    StringCMD(Device * device, const QString &stringValue);
    
    QString toQStringCMD() const override;
    void execute() override;
    
protected:
    // 字符串型设备的值
    QString stringValue_;
};

#endif // STRINGCMD_H
