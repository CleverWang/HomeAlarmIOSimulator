#ifndef KEYCMD_H
#define KEYCMD_H

#include "cmd.h"

// 按键型命令
class KeyCMD : public CMD
{
public:
    KeyCMD(const Device * const device);
    
    QString toQStringCMD() const override;
};

#endif // KEYCMD_H
