#include "FrameDiff.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

FrameDiff::FrameDiff(Video::sptr video1, Video::sptr video2) : video1(video1), video2(video2) {}

FrameDiff::~FrameDiff() {}

unsigned int FrameDiff::getFrameCount() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}

    return qMin(video1->getFrameCount(), video2->getFrameCount());
}

Video::sptr FrameDiff::getVideo1() {
    return video1;
}

Video::sptr FrameDiff::getVideo2() {
    return video2;
}

Memento FrameDiff::getMemento() const {
    Memento memento;

    memento.setSharedPointer("video1", video1);
    memento.setSharedPointer("video2", video2);

    return memento;
}

void FrameDiff::restore(Memento memento) {
    video1 = memento.getSharedPointer("video1").dynamicCast<Video>();
    video2 = memento.getSharedPointer("video2").dynamicCast<Video>();
}

FrameDiff::FrameDiff() {
    isDummyFlag = true;
}

Saveable::SaveableType FrameDiff::getSaveableType() {
    return SaveableType::frameDiff;
}

}  // namespace difference
}  // namespace model