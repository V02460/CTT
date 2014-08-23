#include "FFmpegException.h"

namespace exception {

FFmpegException::FFmpegException() : msg(""){
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName();
#endif
}

FFmpegException::FFmpegException(QString msg) : msg(msg), asciiMsg(msg.toLatin1()) {
#ifdef DEBUG_EXCEPTION_PRINT_ON_CALL
    qDebug() << getName() << getMsg();
#endif
}

FFmpegException::~FFmpegException() {

}

QString FFmpegException::getMsg() const {
    return msg;
}

const char *FFmpegException::what() const {
    return asciiMsg.constData();
}

void FFmpegException::raise() const {
    throw *this;
}

FFmpegException *FFmpegException::clone() const {
    return new FFmpegException(*this);
}

}