#ifndef _ACCESSTODUMMYEXCEPTION_H
#define _ACCESSTODUMMYEXCEPTION_H

#include <QString>

#include "RuntimeException.h"

namespace exception {

class AccessToDummyException :  public RuntimeException {
public:
    /**
    * Creates a new IllegalArgumentException.
    */
    AccessToDummyException();

    /**
    * Creates a new IllegalArgumentException with an error message.
    *
    * @param msg descriptive error message
    */
    AccessToDummyException(QString msg);

    /**
    * Destroys the IllegalArgumentException.
    */
    ~AccessToDummyException();

    virtual QString getName() const Q_DECL_OVERRIDE { return "AccessToDummyException"; }
    virtual QString getMsg() const Q_DECL_OVERRIDE;
    virtual const char *what() const Q_DECL_OVERRIDE;

    virtual void raise() const Q_DECL_OVERRIDE;
    virtual AccessToDummyException *clone() const Q_DECL_OVERRIDE;
private:
    const QString msg;
    const QByteArray asciiMsg;
};
}  // namespace exception

#endif  //_ACCESSTODUMMYEXCEPTION_H