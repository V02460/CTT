#include "NotImplementedException.h"

namespace exception {

NotImplementedException::NotImplementedException() : msg(""){
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName();
#endif
}

NotImplementedException::NotImplementedException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName() << getMsg();
#endif
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