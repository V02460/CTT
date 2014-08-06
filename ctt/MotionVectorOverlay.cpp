#include "MotionVectorOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

MotionVectorOverlay::MotionVectorOverlay(Module::sptr predecessor) : Overlay(predecessor) {
    throw new NotImplementedException();
}

MotionVectorOverlay::~MotionVectorOverlay () {
    throw new NotImplementedException();
}

QString MotionVectorOverlay::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MotionVectorOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType MotionVectorOverlay::getType() const {
	return Saveable::SaveableType::motionVektorOverlay;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model