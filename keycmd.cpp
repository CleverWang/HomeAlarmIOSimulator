#include "keycmd.h"

KeyCMD::KeyCMD(Device * device) :
    CMD(device)
{
    
}

QString KeyCMD::toQStringCMD() const
{
    // 发送”设备类型 设备号”即可
    return CMD::toQStringCMD();
}
