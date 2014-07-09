#ifndef _RUNTIMEEXCEPTION_H
#define _RUNTIMEEXCEPTION_H

#include <QException>

namespace exception {

class RuntimeException : public QException {
public:
    virtual ~RuntimeException() = 0 {};

    virtual QString getName() const = 0;
    virtual QString getMsg() const = 0;
};

}  // namespace exception

#endif