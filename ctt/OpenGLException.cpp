#include "OpenGLException.h"

namespace exception {

OpenGLException::OpenGLException() : msg(""){
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName();
#endif
}

OpenGLException::OpenGLException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName() << getMsg();
#endif
}

OpenGLException::~OpenGLException() {

}

QString OpenGLException::getMsg() const {
    return msg;
}

const char *OpenGLException::what() const {
    return asciiMsg.constData();
}

void OpenGLException::raise() const {
    throw *this;
}

OpenGLException *OpenGLException::clone() const {
    return new OpenGLException(*this);
}

}