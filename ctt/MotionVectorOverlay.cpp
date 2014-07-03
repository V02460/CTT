#include "MotionVectorOverlay.h"

namespace model {
namespace filter {
namespace overlay {


using ::model::frame::Frame;

MotionVectorOverlay::MotionVectorOverlay(Module::sptr predecessor) : Overlay(predecessor) {

}

MotionVectorOverlay::~MotionVectorOverlay () {

}

bool MotionVectorOverlay::supportsIntervals() const {

}

QString MotionVectorOverlay::getName() const {

}

Frame MotionVectorOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namcespace model