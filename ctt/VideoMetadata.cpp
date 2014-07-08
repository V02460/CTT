#include "VideoMetadata.h"

namespace model {
namespace video {

VideoMetadata::VideoMetadata(QSize size, double fps, unsigned int length, QMap<QString, QString> additionalData):
		size(size), fps(fps), length(length), additionalData(additionalData) {

}

VideoMetadata::VideoMetadata(QSize size, double fps, unsigned int length):
		size(size), fps(fps), length(length) {

}

bool VideoMetadata::hasData(QString key) const {
	return additionalData.contains(key);
}

QString VideoMetadata::getData(QString key) {
	if (hasData(key))
	{
		return additionalData.value(key);
	} 
	else
	{
		QString error = "Data with the label \"" + key + "\" is requested but isn't available!";
		//throw Exception
	}
}

QSize VideoMetadata::getSize() {
	return size;
}

double VideoMetadata::getFPS() {
	return fps;
}

unsigned int VideoMetadata::getLength() {
	return length;
}

}  // namespace video
}  // namespace model