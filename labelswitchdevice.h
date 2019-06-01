#ifndef LABELSWITCHDEVICE_H
#define LABELSWITCHDEVICE_H

#include "switchdevice.h"

// QLabel类型的开关型设备
class LabelSwitchDevice : public SwitchDevice
{
public:
    LabelSwitchDevice(DeviceId deviceId, QObject *device);
};

#endif // LABELSWITCHDEVICE_H
