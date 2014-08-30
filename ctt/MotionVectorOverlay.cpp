#include "MotionVectorOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

const QByteArray MotionVectorOverlay::kFilterID = QT_TR_NOOP("overlay_motionvector");

MotionVectorOverlay::MotionVectorOverlay(Module::sptr predecessor)
        : Overlay(predecessor
        , Module::sptr()
        , 0.5) {
    throw new NotImplementedException();
}

MotionVectorOverlay::~MotionVectorOverlay () {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MotionVectorOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

QList<const ::model::Module*> MotionVectorOverlay::getUsesList() const {
    throw new NotImplementedException();
}

bool MotionVectorOverlay::uses(const ::model::Module &module) const {
    throw new NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model