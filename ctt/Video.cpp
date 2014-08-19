#include "Video.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

using ::model::frame::Frame;

void Video::save(QDir path, VideoFileType fileType) const {
    throw new NotImplementedException();
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

}  // namespace video
}  // namespace model