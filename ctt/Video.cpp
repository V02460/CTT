#include "Video.h"

namespace model {
namespace video {

using ::model::frame::Frame;

void Video::save(QDir path, VideoFileType fileType) const {

}

::model::frame::Frame::sptr Video::getScaledFrame(unsigned int frameNumber, QSize size) const {

}

QSharedPointer<QOpenGLContext> Video::getContext() const {

}

}  // namespace video
}  // namespace model