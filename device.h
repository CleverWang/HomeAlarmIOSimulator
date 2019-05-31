#ifndef DEVICE_H
#define DEVICE_H

// 设备描述类
class Device
{
public:
    
    // 设备类型
    enum class DeviceType
    {
        KeyType = 0, // 按键型
        SwitchType, // 开关型
        DigitType, // 数值型
        StringType // 字符串型
    };
    
    // 开关型设备的可取值
    enum class SwitchValue
    {
        Off = 0,
        On,
        UnknownSwitchValue
    };
    
    // 所有设备ID
    enum class DeviceId
    {
        // 按键
        Key0 = 0,
        Key1,
        Key2,
        Key3,
        Key4,
        Key5,
        Key6,
        Key7,
        Key8,
        Key9,
        KeyHash,
        KeyStar,
        KeyArm,
        KeyDisarm,
        
        // 传感器
        Door1,
        Door2,
        Infrared1,
        Infrared2,
        Water1,
        Water2,
        Smoke1,
        Smoke2,
        Temperature1,
        Temperature2,
        Humidity1,
        Humidity2,
        
        // 电话
        PhoneNum,
        PhoneType,
        PhoneArea
    };
    
};

#endif // DEVICE_H
