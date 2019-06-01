#include "widget.h"
#include "ui_widget.h"
#include "logger.h"
#include "keydevice.h"
#include "checkboxswitchdevice.h"
#include "labelswitchdevice.h"
#include "digitdevice.h"
#include "stringdevice.h"

#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent, quint16 port) :
    QWidget(parent),
    ui(new Ui::Widget),
    tcpServer_(nullptr),
    tcpSocket_(nullptr),
    port_(port)
{
    ui->setupUi(this);
    
    this->setWindowTitle(QString("HomeAlarmIOSimulator(port:%1)").arg(this->port_));
    
    Logger::getLogger().setLogToTextEdit(this->ui->textBrowser_log);
    
    this->initDevices();
    this->setupCMDSenderDevices();
    
    // 创建TCP监听服务器
    this->tcpServer_ = new QTcpServer(this);
    if (this->tcpServer_ != nullptr)
    {
        // 监听指定端口
        if (this->tcpServer_->listen(QHostAddress::Any, this->port_))
        {
            Logger::getLogger() << "TCP server successed to start" 
                                << "listen to port: " + QString::number(this->port_);
            // 新连接会触发newConnection信号
            connect(this->tcpServer_, &QTcpServer::newConnection, this, &Widget::onNewConnection);
        }
        else 
        {
            QString msg = "TCP server failed to listen!";
            Logger::getLogger() << msg << "\n";
            QMessageBox::critical(this, "critical", msg);
        }
    }
    else 
    {
        QString msg = "TCP server failed to start!";
        Logger::getLogger() << msg << "\n";
        QMessageBox::critical(this, "critical", msg);
    }
}

Widget::~Widget()
{
    delete ui;
    this->deleteDevices();
    this->closeConnection();
}

void Widget::closeConnection()
{
    // 通信socket不为空才关闭
    if (this->tcpSocket_ != nullptr)
    {
        QString ip = this->tcpSocket_->peerAddress().toString();
        quint16 port = this->tcpSocket_->peerPort();
        
        this->tcpSocket_->disconnectFromHost();
        this->tcpSocket_->close();
        
        // 关闭之后删除（也可以不删除，会自动删除，但是手动删除可节省内存）
        delete this->tcpSocket_;
        
        QString msg = QString("%1: %2 disconnect successfully!").arg(ip).arg(port);
        Logger::getLogger() <<msg;
        
        // 设置为空，表示当前连接结束
        this->tcpSocket_ = nullptr;
    }
}

// 处理新连接信号
void Widget::onNewConnection()
{
    // 需要先关闭上一个连接，再开始下一个连接
    if (this->tcpSocket_ != nullptr)
    {
        this->cmdHelper.clearReceived();
        this->closeConnection();
    }
    
    this->tcpSocket_ = this->tcpServer_->nextPendingConnection(); // 获取一个通信socket连接
    if (this->tcpSocket_ != nullptr)
    {
        // 设置新的通信socket
        this->cmdHelper.setTcpSocket(this->tcpSocket_);
        
        QString ip = this->tcpSocket_->peerAddress().toString();
        quint16 port = this->tcpSocket_->peerPort();
        
        QString msg = QString("%1: %2 connect successfully!").arg(ip).arg(port);
        Logger::getLogger() <<msg;
        
        // 收到数据会触发readyRead信号
        connect(this->tcpSocket_, &QTcpSocket::readyRead, this, &Widget::onReadyRead);
    }
    else 
    {
        QString msg = "new connection failed!";
        Logger::getLogger() << msg;
        QMessageBox::critical(this, "critical", msg);
    } 
}

// 处理可读信号
void Widget::onReadyRead()
{
    QByteArray arr = this->tcpSocket_->readAll();
    Logger::getLogger() << "receive " + arr + " successed";
    this->cmdHelper.receiveCMD(arr);
}

void Widget::initDevices()
{
    // 按键
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key0)] = new KeyDevice(Device::DeviceId::Key0, this->ui->pushButton_0);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key1)] = new KeyDevice(Device::DeviceId::Key1, this->ui->pushButton_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key2)] = new KeyDevice(Device::DeviceId::Key2, this->ui->pushButton_2);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key3)] = new KeyDevice(Device::DeviceId::Key3, this->ui->pushButton_3);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key4)] = new KeyDevice(Device::DeviceId::Key4, this->ui->pushButton_4);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key5)] = new KeyDevice(Device::DeviceId::Key5, this->ui->pushButton_5);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key6)] = new KeyDevice(Device::DeviceId::Key6, this->ui->pushButton_6);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key7)] = new KeyDevice(Device::DeviceId::Key7, this->ui->pushButton_7);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key8)] = new KeyDevice(Device::DeviceId::Key8, this->ui->pushButton_8);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Key9)] = new KeyDevice(Device::DeviceId::Key9, this->ui->pushButton_9);
    this->devicesMap_[static_cast<int>(Device::DeviceId::KeyHash)] = new KeyDevice(Device::DeviceId::KeyHash, this->ui->pushButton_hash);
    this->devicesMap_[static_cast<int>(Device::DeviceId::KeyStar)] = new KeyDevice(Device::DeviceId::KeyStar, this->ui->pushButton_star);
    this->devicesMap_[static_cast<int>(Device::DeviceId::KeyArm)] = new KeyDevice(Device::DeviceId::KeyArm, this->ui->pushButton_arm);
    this->devicesMap_[static_cast<int>(Device::DeviceId::KeyDisarm)] = new KeyDevice(Device::DeviceId::KeyDisarm, this->ui->pushButton_disarm);
    
    // 传感器
    this->devicesMap_[static_cast<int>(Device::DeviceId::Door1)] = new CheckBoxSwitchDevice(Device::DeviceId::Door1, this->ui->checkBox_door_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Door2)] = new CheckBoxSwitchDevice(Device::DeviceId::Door2, this->ui->checkBox_door_2);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Infrared1)] = new CheckBoxSwitchDevice(Device::DeviceId::Infrared1, this->ui->checkBox_infrared_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Infrared2)] = new CheckBoxSwitchDevice(Device::DeviceId::Infrared2, this->ui->checkBox_infrared_2);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Water1)] = new CheckBoxSwitchDevice(Device::DeviceId::Water1, this->ui->checkBox_water_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Water2)] = new CheckBoxSwitchDevice(Device::DeviceId::Water2, this->ui->checkBox_water_2);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Smoke1)] = new DigitDevice(Device::DeviceId::Smoke1, this->ui->doubleSpinBox_smoke_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Smoke2)] = new DigitDevice(Device::DeviceId::Smoke2, this->ui->doubleSpinBox_smoke_2);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Temperature1)] = new DigitDevice(Device::DeviceId::Temperature1, this->ui->doubleSpinBox_temperature_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Temperature2)] = new DigitDevice(Device::DeviceId::Temperature2, this->ui->doubleSpinBox_temperature_2);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Humidity1)] = new DigitDevice(Device::DeviceId::Humidity1, this->ui->doubleSpinBox_humidity_1);
    this->devicesMap_[static_cast<int>(Device::DeviceId::Humidity2)] = new DigitDevice(Device::DeviceId::Humidity2, this->ui->doubleSpinBox_humidity_2);
    
    // 电话
    this->devicesMap_[static_cast<int>(Device::DeviceId::PhoneNum)] = new StringDevice(Device::DeviceId::PhoneNum, this->ui->lineEdit_phone_num);
    this->devicesMap_[static_cast<int>(Device::DeviceId::PhoneType)] = new StringDevice(Device::DeviceId::PhoneType, this->ui->lineEdit_phone_type);
    this->devicesMap_[static_cast<int>(Device::DeviceId::PhoneArea)] = new StringDevice(Device::DeviceId::PhoneArea, this->ui->lineEdit_phone_area);
    
    // 灯
    LabelSwitchDevice *light = new LabelSwitchDevice(Device::DeviceId::Light, this->ui->label_light);
    light->setOnPixmap(QPixmap(":/res/images/light_on.bmp"));
    light->setOffPixmap(QPixmap(":/res/images/light_off.bmp"));
    this->devicesMap_[static_cast<int>(Device::DeviceId::Light)] = light;
    
    // LED
    LabelSwitchDevice *ledGreen = new LabelSwitchDevice(Device::DeviceId::LEDGreen, this->ui->label_led_green);
    ledGreen->setOnPixmap(QPixmap(":/res/images/led_green_on.bmp"));
    ledGreen->setOffPixmap(QPixmap(":/res/images/led_green_off.bmp"));
    this->devicesMap_[static_cast<int>(Device::DeviceId::LEDGreen)] = ledGreen;
    LabelSwitchDevice *ledRed = new LabelSwitchDevice(Device::DeviceId::LEDRed, this->ui->label_led_red);
    ledRed->setOnPixmap(QPixmap(":/res/images/led_red_on.bmp"));
    ledRed->setOffPixmap(QPixmap(":/res/images/led_red_off.bmp"));
    this->devicesMap_[static_cast<int>(Device::DeviceId::LEDRed)] = ledRed;
    
    this->cmdHelper.setDevicesMap(&this->devicesMap_);
}

void Widget::deleteDevices()
{
    foreach(Device *device, this->devicesMap_)
        delete device;
}

void Widget::setupCMDSenderDevices()
{
    for (QHash<int, Device*>::const_iterator ci = this->devicesMap_.constBegin();
         ci != this->devicesMap_.constEnd();
         ++ci)
    {
        connect(ci.value(), &Device::newCMD, &this->cmdHelper, &CMDHelper::writeCMD);
    }
}
