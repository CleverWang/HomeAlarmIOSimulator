#ifndef CHECKBOXSWITCHDEVICE_H
#define CHECKBOXSWITCHDEVICE_H

#include "switchdevice.h"

// QCheckBox类型的开关型设备
class CheckBoxSwitchDevice : public SwitchDevice
{
public:
    CheckBoxSwitchDevice(DeviceId deviceId, QObject *device);
};

#endif // CHECKBOXSWITCHDEVICE_H
