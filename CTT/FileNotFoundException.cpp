#include "FileNotFoundException.h"

namespace exception {

FileNotFoundException::FileNotFoundException() : msg(""){

}

FileNotFoundException::FileNotFoundException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {

}

FileNotFoundException::~FileNotFoundException() {

}

QString FileNotFoundException::getMsg() const {
    return msg;
}

const char *FileNotFoundException::what() const {
    return asciiMsg.constData();
}

void FileNotFoundException::raise() const {
    throw *this;
}

FileNotFoundException *FileNotFoundException::clone() const {
    return new FileNotFoundException(*this);
}

}