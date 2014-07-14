#include "OpenGLException.h"

namespace exception {

OpenGLException::OpenGLException() : msg(""){

}

OpenGLException::OpenGLException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {

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