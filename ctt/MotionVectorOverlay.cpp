#include "MotionVectorOverlay.h"

namespace model {
namespace filter {
namespace overlay {


using ::model::frame::Frame;

MotionVectorOverlay::MotionVectorOverlay(Module::sptr predecessor) : Overlay(predecessor) {

}

MotionVectorOverlay::~MotionVectorOverlay () {

}

QString MotionVectorOverlay::getName() const {

}

model::frame::Frame::sptr MotionVectorOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namespace model