#include "IllegalArgumentException.h"

namespace exception {

IllegalArgumentException::IllegalArgumentException() : msg("") {

}

IllegalArgumentException::IllegalArgumentException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {

}

IllegalArgumentException::~IllegalArgumentException() {

}

QString IllegalArgumentException::getMsg() const {
    return msg;
}

const char *IllegalArgumentException::what() const {
    return asciiMsg.constData();
}

void IllegalArgumentException::raise() const {
    throw *this;
}

IllegalArgumentException *IllegalArgumentException::clone() const {
    return new IllegalArgumentException(*this);
}

}  // namespace exception