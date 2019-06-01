#include "labelswitchdevice.h"

#include <QLabel>
#include <QDebug>

LabelSwitchDevice::LabelSwitchDevice(DeviceId deviceId, QObject *device) :
    SwitchDevice (deviceId, device)
{
    
}

void LabelSwitchDevice::executeCMD(Device::SwitchValue switchValue)
{
    // 标签开关型设备使用QLabel
    QLabel *label = dynamic_cast<QLabel *>(this->device_);
    if (label != nullptr)
    {
        switch (switchValue) 
        {
        case Device::SwitchValue::On:
            label->setPixmap(this->onPixmap_);
            break;
        case Device::SwitchValue::Off:
            label->setPixmap(this->offPixmap_);
            break;
        default:
            ;
        }
    }
    else
    {
        qDebug() << "cast to QLabel failed";
    }
}

QPixmap LabelSwitchDevice::onPixmap() const
{
    return onPixmap_;
}

void LabelSwitchDevice::setOnPixmap(const QPixmap &onPixmap)
{
    onPixmap_ = onPixmap;
}

QPixmap LabelSwitchDevice::offPixmap() const
{
    return offPixmap_;
}

void LabelSwitchDevice::setOffPixmap(const QPixmap &offPixmap)
{
    offPixmap_ = offPixmap;
}
