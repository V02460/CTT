#ifndef _PARSEEXCEPTION_H
#define _PARSEEXCEPTION_H

#include <QException>
#include <QString>

#include "RuntimeException.h"

namespace exception {

/**
 * Thrown to indicate that a method has been passed an illegal or inappropriate argument.
 */
class ParseException : public RuntimeException {
public:
    /**
    * Creates a new ParseException.
    */
    ParseException();

    /**
    * Creates a new ParseException with an error message.
    *
    * @param msg descriptive error message
    */
    ParseException(QString msg);

    /**
    * Destroys the ParseException.
    */
    ~ParseException();

    virtual QString getName() const Q_DECL_OVERRIDE { return "ParseException"; }
    virtual QString getMsg() const Q_DECL_OVERRIDE;
    virtual const char *what() const Q_DECL_OVERRIDE;

    virtual void ParseException::raise() const Q_DECL_OVERRIDE;
    virtual ParseException *clone() const Q_DECL_OVERRIDE;
private:
    const QString msg;
    const QByteArray asciiMsg;
};

}  // namespace exception

#endif