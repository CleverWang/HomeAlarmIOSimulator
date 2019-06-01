#ifndef CMD_H
#define CMD_H

#include <limits>

#include <QString>

#include "device.h"

// 命令基类
class CMD
{
public:
    static QString startDelimiter();
    static void setStartDelimiter(const QString &startDelimiter);
    
    static QString stopDelimiter();
    static void setStopDelimiter(const QString &stopDelimiter);
    
    CMD(const Device * const device);
    
    virtual ~CMD();
    
    // 不同设备类型的命令可以override
    virtual QString toQStringCMD() const;
    
protected:
    // 起始分隔符
    static QString startDelimiter_;
    // 结束分隔符
    static QString stopDelimiter_;
    
    // 设备
    const Device * const device_;
};

#endif // CMD_H
