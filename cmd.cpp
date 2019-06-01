#include "cmd.h"

QString CMD::startDelimiter_ = ">";
QString CMD::stopDelimiter_ = "<";

QString CMD::startDelimiter()
{
    return startDelimiter_;
}

void CMD::setStartDelimiter(const QString &startDelimiter)
{
    startDelimiter_ = startDelimiter;
}

QString CMD::stopDelimiter()
{
    return stopDelimiter_;
}

void CMD::setStopDelimiter(const QString &stopDelimiter)
{
    stopDelimiter_ = stopDelimiter;
}

CMD::CMD(Device * device) : 
    device_(device)
{
    
}

CMD::~CMD()
{
    
}

QString CMD::toQStringCMD() const
{
    QString output;
    output.append(CMD::startDelimiter_);
    output.append(QString("%1 %2")
                  .arg(static_cast<int>(this->device_->deviceType()))
                  .arg(static_cast<int>(this->device_->deviceId())));
    output.append(CMD::stopDelimiter_);
    
    return output;
}

void CMD::execute()
{
    
}
