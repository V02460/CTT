#include "ParseException.h"

namespace exception {
	
ParseException::ParseException() : msg("") {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName();
#endif
}

ParseException::ParseException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName() << getMsg();
#endif
}

ParseException::~ParseException() {

}

QString ParseException::getMsg() const {
    return msg;
}

const char *ParseException::what() const {
    return asciiMsg.constData();
}

void ParseException::raise() const {
    throw *this;
}

ParseException *ParseException::clone() const {
    return new ParseException(*this);
}

}  // namespace exception