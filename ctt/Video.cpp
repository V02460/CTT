#include "Video.h"

#include "NotImplementedException.h"
#include "YUVType.h"
#include "IOException.h"

namespace model {
namespace video {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::exception::IOException;

using ::model::frame::Frame;

void Video::save(QString path, YUVType type) const
{
    throw new NotImplementedException();

	if (isDummy()) {
		throw new IllegalStateException("Tried to save a dummy video.");
	}

	QFile videoFile(path);
	
	if (videoFile.exists())
	{
		videoFile.remove();
	}

	if (!videoFile.open(QIODevice::WriteOnly)) {
		throw new IOException("Can't open the file at \"" + path + "\".");
	}

	QDataStream stream(&videoFile);

	int bytesPerFrame = 0;

	switch (type)
	{
	case YUV444:
		bytesPerFrame = 3 * getResolution().width() * getResolution().height();
		break;
	case YUV422:
		if ((getResolution().width() % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV422 format.");
		}
		bytesPerFrame = 2 * getResolution().width() * getResolution().height();
		break;
	case YUV420:
		if ((getResolution().width() % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
		}
		if ((getResolution().height() % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
		}
		bytesPerFrame = (3 * getResolution().width() * getResolution().height()) / 2;
		break;
	}

	for (unsigned int i; i < getFrameCount(); i++)
	{
		//TODO szeg get the data and write it
	}

	if (!videoFile.flush())
	{
		throw new IOException("Can't flush the file at \"" + path + "\".");
	}
	
	videoFile.close();
}

::model::frame::Frame::sptr Video::getScaledFrame(unsigned int frameNumber, QSize size) const {
    throw new NotImplementedException();
}

QSharedPointer<QOpenGLContext> Video::getContext() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the context of a dummy video.");
	}
	return context;
}

QSize Video::getResolution() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the resolution of a dummy video.");
	}
	return getMetadata().getSize();
}

}  // namespace video
}  // namespace model