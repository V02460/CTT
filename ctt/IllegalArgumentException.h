#ifndef _ILLEGALARGUMENTEXCEPTION_H
#define _ILLEGALARGUMENTEXCEPTION_H

#include <QString>

#include "RuntimeException.h"

namespace exception {

/**
 * Thrown to indicate that a method has been passed an illegal or inappropriate argument.
 */
class IllegalArgumentException : public RuntimeException {
public:
    /**
    * Creates a new IllegalArgumentException.
    */
    IllegalArgumentException();

    /**
    * Creates a new IllegalArgumentException with an error message.
    *
    * @param msg descriptive error message
    */
    IllegalArgumentException(QString msg);

    /**
    * Destroys the IllegalArgumentException.
    */
    ~IllegalArgumentException();

    virtual QString getName() const Q_DECL_OVERRIDE { return "IllegalArgumentException"; }
    virtual QString getMsg() const Q_DECL_OVERRIDE;
    virtual const char *what() const Q_DECL_OVERRIDE;

    virtual void raise() const Q_DECL_OVERRIDE;
    virtual IllegalArgumentException *clone() const Q_DECL_OVERRIDE;
private:
    const QString msg;
    const QByteArray asciiMsg;
};

}  // namespace exception

#endif