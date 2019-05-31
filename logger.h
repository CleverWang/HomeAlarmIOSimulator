#ifndef LOGGER_H
#define LOGGER_H

#include <ostream>
#include <iostream>

#include <QTextEdit>

class Logger
{
    friend Logger &operator<<(Logger &logger, const QString &msg);
public:
    static Logger &getLogger();
    
    void setLogToTextEdit(QTextEdit *textEditOut);
    void setLogToOstream(std::ostream *out);
    
    void enableLogger();
    void disableLogger();
    
private:
    static Logger logger_;
    
    Logger(std::ostream *out = &std::cout);
    
    void logToTextEdit(const QString &msg);
    void logToOstream(const QString &msg);
    
    std::ostream *out_;
    QTextEdit *textEditOut_;
    bool enabled_;
};

Logger &operator<<(Logger &logger, const QString &msg);

#endif // LOGGER_H
