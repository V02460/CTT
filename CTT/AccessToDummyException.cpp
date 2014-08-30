#include "AccessToDummyException.h"

namespace exception {

AccessToDummyException::AccessToDummyException() : msg("") {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName();
#endif
}

AccessToDummyException::AccessToDummyException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName() << getMsg();
#endif
}

AccessToDummyException::~AccessToDummyException() {

}

QString AccessToDummyException::getMsg() const {
    return msg;
}

const char *AccessToDummyException::what() const {
    return asciiMsg.constData();
}

void AccessToDummyException::raise() const {
    throw *this;
}

AccessToDummyException *AccessToDummyException::clone() const {
    return new AccessToDummyException(*this);
}


}  // namespace exception