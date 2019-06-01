#include "stringdevice.h"
#include <QLineEdit>
#include <QDebug>

StringDevice::StringDevice(DeviceId deviceId, QObject *device) :
    Device (Device::DeviceType::StringType, deviceId, device)
{
    
}

void StringDevice::executeCMD(const QString &string)
{
    QLineEdit *linEdit = dynamic_cast<QLineEdit *>(this->device_);
    if (linEdit != nullptr)
    {
        linEdit->setText(string);
    }
    else
    {
        qDebug() << "cast to QLineEdit failed";
    }
}
