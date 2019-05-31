#include "logger.h"

#include <QDateTime>

Logger Logger::logger_;

Logger &Logger::getLogger()
{
    return logger_;
}

Logger::Logger(std::ostream *out) : out_(out), textEditOut_(nullptr), enabled_(true)
{
    
}

void Logger::setLogToTextEdit(QTextEdit *textEditOut)
{
    this->textEditOut_ = textEditOut;
    this->out_ = nullptr;
}

void Logger::logToTextEdit(const QString &msg)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("[yyyy-MM-dd hh:mm:ss]: ");
    this->textEditOut_->append(current_date + msg);
}

void Logger::setLogToOstream(std::ostream *out)
{
    this->out_ = out;
    this->textEditOut_ = nullptr;
}

void Logger::enableLogger()
{
    this->enabled_ = true;
}

void Logger::disableLogger()
{
    this->enabled_ = false;
}

void Logger::logToOstream(const QString &msg)
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("[yyyy-MM-dd hh:mm:ss]: ");
    (*(this->out_)) << current_date.toStdString() << msg.toStdString() << std::endl;
}

Logger &operator<<(Logger &logger, const QString &msg)
{
    if (logger.enabled_)
    {
        if (logger.textEditOut_ != nullptr)
        {
            logger.logToTextEdit(msg);
        }
        else 
        {
            logger.logToOstream(msg);
        }
    }
    return logger;
}


