#include "MotionVectorOverlay.h"

#include "NotImplementedException.h"

// TODO bitte saveable dinge bei implementierung beachten

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

const QByteArray MotionVectorOverlay::kFilterID = QT_TRANSLATE_NOOP("Filter", "overlay_motionvector");

MotionVectorOverlay::MotionVectorOverlay(Module::sptr predecessor)
        : Overlay(predecessor
        , Module::sptr()
        , 0.5) {
    throw NotImplementedException();
}

MotionVectorOverlay::~MotionVectorOverlay () {
    throw NotImplementedException();
}

model::frame::Frame::sptr MotionVectorOverlay::getFrame(unsigned int frameNumber) const {
    throw NotImplementedException();
}

void MotionVectorOverlay::restore(::model::saveable::Memento memento) {
	throw NotImplementedException();
}

QList<const Module*> MotionVectorOverlay::getUsesList() const {
	throw NotImplementedException();
}

Saveable::sptr MotionVectorOverlay::getDummy() {
	throw IllegalArgumentException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model