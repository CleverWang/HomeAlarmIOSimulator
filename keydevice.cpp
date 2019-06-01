#include "keydevice.h"
#include "keycmd.h"

#include <QAbstractButton>
#include <QDebug>

KeyDevice::KeyDevice(DeviceId deviceId, QObject *device) : 
    Device(Device::DeviceType::KeyType, deviceId, device)
{
    // 按键型设备使用QpushButton
    QAbstractButton *button = dynamic_cast<QAbstractButton *>(this->device_);
    if (button != nullptr)
    {
        // 按键点击后发送命令
        QObject::connect(button, &QAbstractButton::clicked, 
                         [this]()
        {
            emit this->newCMD(KeyCMD(this).toQStringCMD());
        });
    }
    else 
    {
        qDebug() << "cast to QAbstractButton failed";
    }
}
