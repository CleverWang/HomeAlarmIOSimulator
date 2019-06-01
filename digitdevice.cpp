#include "digitdevice.h"
#include "digitcmd.h"

#include <QDoubleSpinBox>
#include <QDebug>

DigitDevice::DigitDevice(DeviceId deviceId, QObject *device) :
    Device (Device::DeviceType::DigitType, deviceId, device)
{
    // 数字型设备使用QDoubleSpinBox
    QDoubleSpinBox *doubleSpinBox = dynamic_cast<QDoubleSpinBox *>(this->device_);
    if (doubleSpinBox != nullptr)
    {
        // QDoubleSpinBox值改变时发送命令
        QObject::connect(doubleSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
                [this](double d)
        {
            emit this->newCMD(DigitCMD(this, d).toQStringCMD());
        });
    }
    else
    {
        qDebug() << "cast to QDoubleSpinBox failed";
    }
}
