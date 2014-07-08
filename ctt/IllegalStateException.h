#ifndef _ILLEGALSTATEEXCEPTION_H
#define _ILLEGALSTATEEXCEPTION_H

#include <QException>
#include <QString>

#include "RuntimeException.h"

namespace exception {

/**
 * Signals that a method has been invoked at an illegal or inappropriate time.
 */
class IllegalStateException : public RuntimeException {
public:
    /**
     * Creates a new IllegalStateException.
     */
    IllegalStateException();

    /**
     * Creates a new IllegalStateException with an error message.
     *
     * @param msg descriptive error message
     */
    IllegalStateException(QString msg);

    /**
     * Destroys the IllegalStateException.
     */
    ~IllegalStateException();

    virtual QString getName() const Q_DECL_OVERRIDE{ return "IllegalStateException"; }
    virtual QString getMsg() const Q_DECL_OVERRIDE;
    const char *what() const Q_DECL_OVERRIDE;

    virtual void IllegalStateException::raise() const Q_DECL_OVERRIDE;
    virtual IllegalStateException *clone() const Q_DECL_OVERRIDE;

private:
    const QString msg;
    const QByteArray asciiMsg;
};

}  // namespace exception

#endif