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
    
    CMD(Device * device);
    
    virtual ~CMD();
    
    // 不同设备类型的命令可以override
    virtual QString toQStringCMD() const;
    // 执行接收到的命令（将参数转发给对应设备）
    virtual void execute();
    
protected:
    // 起始分隔符
    static QString startDelimiter_;
    // 结束分隔符
    static QString stopDelimiter_;
    
    // 设备
    Device * device_;
};

#endif // CMD_H
