#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

// 设备基类
class Device: public QObject
{
    Q_OBJECT
public:
    // 所有设备类型
    enum class DeviceType
    {
        KeyType = 0, // 按键型
        SwitchType = 1, // 开关型
        DigitType = 2, // 数值型
        StringType = 3 // 字符串型
    };
    
    // 所有设备ID
    enum class DeviceId
    {
        // 按键
        Key0 = 0,
        Key1 = 1,
        Key2 = 2,
        Key3 = 3,
        Key4 = 4,
        Key5 = 5,
        Key6 = 6,
        Key7 = 7,
        Key8 = 8,
        Key9 = 9,
        KeyHash = 10,
        KeyStar = 11,
        KeyArm = 12,
        KeyDisarm = 13,
        
        // 传感器
        Door1 = 14,
        Door2 = 15,
        Infrared1 = 16,
        Infrared2 = 17,
        Water1 = 18,
        Water2 = 19,
        Smoke1 = 20,
        Smoke2 = 21,
        Temperature1 = 22,
        Temperature2 = 23,
        Humidity1 = 24,
        Humidity2 = 25,
        
        // 电话
        PhoneNum = 26,
        PhoneType = 27,
        PhoneArea = 28
    };
    
    // 开关型设备的可取值
    enum class SwitchValue
    {
        Off = 0,
        On = 1,
        UnknownSwitchValue = 2
    };
    
    Device(DeviceType deviceType, DeviceId deviceId, QObject *device);
    
    DeviceType deviceType() const;
    void setDeviceType(const DeviceType &deviceType);
    
    DeviceId deviceId() const;
    void setDeviceId(const DeviceId &deviceId);
    
    QObject *device() const;
    void setDevice(QObject *device);
    
protected:
    DeviceType deviceType_; // 设备类型
    DeviceId deviceId_; // 设备ID
    QObject *device_; // 实际设备
    
signals:
    // 设备可以发送新的命令信号
    void newCMD(const QString &cmd);
};

#endif // DEVICE_H
