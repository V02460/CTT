#include "VideoMetadata.h"
#include "IllegalArgumentException.h"

namespace model {
namespace video {
	
	VideoMetadata::VideoMetadata(QSize size, double fps, unsigned int length, QMap<QString, QString> additionalData) :
		VideoMetadata(size, fps, length) {
		this->additionalData = additionalData;
}

VideoMetadata::VideoMetadata(QSize size, double fps, unsigned int length):
		size(size), fps(fps), length(length) {
	if (size.height() == 0) {
		throw exception::IllegalArgumentException("Tried to create a VideoMetadata object describing a video "
			"height of 0!");
	}
	if (size.width() == 0) {
		throw exception::IllegalArgumentException("Tried to create a VideoMetadata object describing a video "
			"a width of 0!");
	}
	if (!(fps > 0)) {
		throw exception::IllegalArgumentException("Tried to create a VideoMetadata object describing a video "
			"playback speed of 0 frames per second!");
	}
	if (length == 0) {
		throw exception::IllegalArgumentException("Tried to create a VideoMetadata object describing a video "
			"length of 0 frames!");
	}
}

bool VideoMetadata::hasData(QString key) const {
	return additionalData.contains(key);
}

QString VideoMetadata::getData(QString key) const {
	if (hasData(key))
	{
		return additionalData.value(key);
	} 
	else
	{
		throw exception::IllegalArgumentException("Data with the label \"" + key 
			+ "\" is requested but isn't available!");
	}
}

QSize VideoMetadata::getSize()  const{
	return size;
}

double VideoMetadata::getFPS()  const{
	return fps;
}

unsigned int VideoMetadata::getLength()  const{
	return length;
}

QMap<QString, QString> VideoMetadata::getAdditionalMetadata() const
{
	return additionalData;
}

}  // namespace video
}  // namespace model