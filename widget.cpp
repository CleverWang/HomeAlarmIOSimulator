#include "widget.h"
#include "ui_widget.h"
#include "logger.h"

#include <QMessageBox>
#include <QDebug>

Widget::Widget(QWidget *parent, quint16 port) :
    QWidget(parent),
    ui(new Ui::Widget),
    tcpServer_(nullptr),
    tcpSocket_(nullptr),
    port_(port),
    cmdHelper(new CMDHelper)
{
    ui->setupUi(this);
    
    this->setWindowTitle(QString("HomeAlarmIOSimulator(port:%1)").arg(this->port_));
    
    Logger::getLogger().setLogToTextEdit(this->ui->textBrowser_log);
    
    this->setupUISignalSlot();
    
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
        this->closeConnection();
    
    this->tcpSocket_ = this->tcpServer_->nextPendingConnection(); // 获取一个通信socket连接
    if (this->tcpSocket_ != nullptr)
    {
        // 设置新的通信socket
        this->cmdHelper->setTcpSocket(this->tcpSocket_);
        
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
    
}

void Widget::setupUISignalSlot()
{
    // 按键
    connect(this->ui->pushButton_0, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key0));
    });
    connect(this->ui->pushButton_1, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key1));
    });
    connect(this->ui->pushButton_2, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key2));
    });
    connect(this->ui->pushButton_3, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key3));
    });
    connect(this->ui->pushButton_4, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key4));
    });
    connect(this->ui->pushButton_5, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key5));
    });
    connect(this->ui->pushButton_6, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key6));
    });
    connect(this->ui->pushButton_7, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key7));
    });
    connect(this->ui->pushButton_8, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key8));
    });
    connect(this->ui->pushButton_9, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::Key9));
    });
    connect(this->ui->pushButton_hash, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::KeyHash));
    });
    connect(this->ui->pushButton_star, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::KeyStar));
    });
    
    connect(this->ui->pushButton_arm, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::KeyArm));
    });
    connect(this->ui->pushButton_disarm, &QPushButton::clicked, 
            [this]()
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::KeyType, Device::DeviceId::KeyDisarm));
    });
    
    // 开关型
    connect(this->ui->checkBox_door_1, &QCheckBox::stateChanged, 
            [this](int state)
    {
        if (state == Qt::Checked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Door1, Device::SwitchValue::On));
        else if (state == Qt::Unchecked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Door1, Device::SwitchValue::Off));
    });
    connect(this->ui->checkBox_door_2, &QCheckBox::stateChanged, 
            [this](int state)
    {
        if (state == Qt::Checked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Door2, Device::SwitchValue::On));
        else if (state == Qt::Unchecked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Door2, Device::SwitchValue::Off));
    });
    connect(this->ui->checkBox_infrared_1, &QCheckBox::stateChanged, 
            [this](int state)
    {
        if (state == Qt::Checked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Infrared1, Device::SwitchValue::On));
        else if (state == Qt::Unchecked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Infrared1, Device::SwitchValue::Off));
    });
    connect(this->ui->checkBox_infrared_2, &QCheckBox::stateChanged, 
            [this](int state)
    {
        if (state == Qt::Checked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Infrared2, Device::SwitchValue::On));
        else if (state == Qt::Unchecked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Infrared2, Device::SwitchValue::Off));
    });
    connect(this->ui->checkBox_water_1, &QCheckBox::stateChanged, 
            [this](int state)
    {
        if (state == Qt::Checked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Water1, Device::SwitchValue::On));
        else if (state == Qt::Unchecked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Water1, Device::SwitchValue::Off));
    });
    connect(this->ui->checkBox_water_2, &QCheckBox::stateChanged, 
            [this](int state)
    {
        if (state == Qt::Checked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Water2, Device::SwitchValue::On));
        else if (state == Qt::Unchecked)
            this->cmdHelper->writeCMD(CMD(Device::DeviceType::SwitchType, Device::DeviceId::Water2, Device::SwitchValue::Off));
    });
    
    // 数字型
    connect(this->ui->doubleSpinBox_smoke_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double d)
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::DigitType, Device::DeviceId::Smoke1, d));
    });
    connect(this->ui->doubleSpinBox_smoke_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double d)
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::DigitType, Device::DeviceId::Smoke2, d));
    });
    connect(this->ui->doubleSpinBox_temperature_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double d)
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::DigitType, Device::DeviceId::Temperature1, d));
    });
    connect(this->ui->doubleSpinBox_temperature_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double d)
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::DigitType, Device::DeviceId::Temperature2, d));
    });
    connect(this->ui->doubleSpinBox_humidity_1, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double d)
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::DigitType, Device::DeviceId::Humidity1, d));
    });
    connect(this->ui->doubleSpinBox_humidity_2, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
            [this](double d)
    {
        this->cmdHelper->writeCMD(CMD(Device::DeviceType::DigitType, Device::DeviceId::Humidity2, d));
    });
}
