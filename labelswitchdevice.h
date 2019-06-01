#ifndef LABELSWITCHDEVICE_H
#define LABELSWITCHDEVICE_H

#include "switchdevice.h"

#include <QPixmap>

// QLabel类型的开关型设备
class LabelSwitchDevice : public SwitchDevice
{
public:
    LabelSwitchDevice(DeviceId deviceId, QObject *device);

    void executeCMD(SwitchValue switchValue) override;

    QPixmap onPixmap() const;
    void setOnPixmap(const QPixmap &onPixmap);
    
    QPixmap offPixmap() const;
    void setOffPixmap(const QPixmap &offPixmap);
    
private:
    QPixmap onPixmap_; // 启动时展示的图片
    QPixmap offPixmap_; // 关闭时展示的图片
};

#endif // LABELSWITCHDEVICE_H
