#include "VideoMetadata.h"

namespace model {
namespace video {

VideoMetadata::VideoMetadata(QSize size, double fps, unsigned int length, QMap<QString, QString> additionalData) {

}

VideoMetadata::VideoMetadata(QSize size, double fps, unsigned int length) {

}

bool VideoMetadata::hasData(QString key) const {

}

QString VideoMetadata::getData(QString key) {

}

QSize VideoMetadata::getSize() {

}

double VideoMetadata::getFPS() {

}

unsigned int VideoMetadata::getLength() {

}

}  // namespace video
}  // namespace model