#include "IOException.h"

namespace exception {

IOException::IOException() : msg(""){

}

IOException::IOException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {

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