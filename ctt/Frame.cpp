#include "Frame.h"

namespace model {
namespace frame {

using ::model::frame::histogram::Histogram;
using ::model::frame::histogram::HistogramType;

Frame::Frame(QSharedPointer<QOpenGLContext> context, QImage image, FrameMetadata metadata) {

}

FrameMetadata Frame::getMetadata() const {

}

Histogram::sptr Frame::getHistogram(HistogramType type) const {

}

}  // namespace frame
}  // namespace model