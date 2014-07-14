#include "Video.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::exception::NotImplementedException;

using ::model::frame::Frame;

void Video::save(QDir path, VideoFileType fileType) const {
    throw new NotImplementedException();
}

::model::frame::Frame::sptr Video::getScaledFrame(unsigned int frameNumber, QSize size) const {
    throw new NotImplementedException();
}

QSharedPointer<QOpenGLContext> Video::getContext() const {
    throw new NotImplementedException();
}

}  // namespace video
}  // namespace model