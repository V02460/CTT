#include "IllegalStateException.h"

namespace exception {

IllegalStateException::IllegalStateException() : msg(""){

}

IllegalStateException::IllegalStateException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {

}

IllegalStateException::~IllegalStateException() {

}

QString IllegalStateException::getMsg() const {
    return msg;
}

const char *IllegalStateException::what() const {
    return asciiMsg.constData();
}

void IllegalStateException::raise() const {
    throw *this;
}

IllegalStateException *IllegalStateException::clone() const {
    return new IllegalStateException(*this);
}

}