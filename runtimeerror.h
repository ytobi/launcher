#ifndef RUNTIMEERROR_H
#define RUNTIMEERROR_H

#include <QByteArray>
#include <QException>

class RuntimeError : public QException
{
public:
    RuntimeError(const QString &msg);
    const char *what() const noexcept;

private:
    const char *data;
};

#endif // RUNTIMEERROR_H
