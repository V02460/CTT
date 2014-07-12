#ifndef _OPENGLEXCEPTION_H
#define _OPENGLEXCEPTION_H

#include <QException>
#include <QString>

#include "RuntimeException.h"

namespace exception {

/**
* Signals that a method has been invoked at an illegal or inappropriate time.
*/
class OpenGLException : public RuntimeException {
public:
    /**
    * Creates a new OpenGLException.
    */
    OpenGLException();

    /**
    * Creates a new OpenGLException with an error message.
    *
    * @param msg descriptive error message
    */
    OpenGLException(QString msg);

    /**
    * Destroys the OpenGLException.
    */
    ~OpenGLException();

    virtual QString getName() const Q_DECL_OVERRIDE{return "OpenGLException";}
    virtual QString getMsg() const Q_DECL_OVERRIDE;
    const char *what() const Q_DECL_OVERRIDE;

    virtual void OpenGLException::raise() const Q_DECL_OVERRIDE;
    virtual OpenGLException *clone() const Q_DECL_OVERRIDE;

private:
    const QString msg;
    const QByteArray asciiMsg;
};

}  // namespace exception

#endif  //_OPENGLEXCEPTION_H