#include "NotImplementedException.h"

namespace exception {

NotImplementedException::NotImplementedException() : msg(""){

}

NotImplementedException::NotImplementedException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {

}

NotImplementedException::~NotImplementedException() {

}

QString NotImplementedException::getMsg() const {
    return msg;
}

const char *NotImplementedException::what() const {
    return asciiMsg.constData();
}

void NotImplementedException::raise() const {
    throw *this;
}

NotImplementedException *NotImplementedException::clone() const {
    return new NotImplementedException(*this);
}

}