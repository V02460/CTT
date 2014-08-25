#include "IOException.h"

namespace exception {

IOException::IOException() : msg("") {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName();
#endif
}

IOException::IOException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName() << getMsg();
#endif
}

IOException::~IOException() {

}

QString IOException::getMsg() const {
    return msg;
}

const char *IOException::what() const {
    return asciiMsg.constData();
}

void IOException::raise() const {
    throw *this;
}

IOException *IOException::clone() const {
	return new IOException(*this);
}

}