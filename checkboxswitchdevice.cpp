#include "checkboxswitchdevice.h"
#include "switchcmd.h"

#include <QCheckBox>
#include <QDebug>

CheckBoxSwitchDevice::CheckBoxSwitchDevice(DeviceId deviceId, QObject *device) :
    SwitchDevice (deviceId, device)
{
    QCheckBox *checkBox = dynamic_cast<QCheckBox *>(this->device_);
    if (checkBox != nullptr)
    {
        // QCheckBox状态改变时发送命令
        QObject::connect(checkBox, &QCheckBox::stateChanged, 
                [this](int state)
        {
            if (state == Qt::Checked)
                emit this->newCMD(SwitchCMD(this, Device::SwitchValue::On).toQStringCMD());
            else if (state == Qt::Unchecked)
                emit this->newCMD(SwitchCMD(this, Device::SwitchValue::Off).toQStringCMD());
        });
    }
    else
    {
        qDebug() << "cast to QCheckBox failed";
    }
}
