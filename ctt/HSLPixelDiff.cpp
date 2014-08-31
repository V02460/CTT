#include "HSLPixelDiff.h"

#include "NotImplementedException.h"
#include "GPUSurfaceShader.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::helper::GPUSurfaceShader;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : AveragePixelDiff(video1, video2) {
}

HSLPixelDiff::~HSLPixelDiff() {
}

Surface::sptr HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {
    if (isDummy()) {
        throw AccessToDummyException();
    }
    if (frameNr >= getFrameCount()) {
        throw IllegalArgumentException("Requested frame number " +
                                       QString::number(frameNr) +
                                       " where only " +
                                       QString::number(getFrameCount()) +
                                       " frames exist.");
    }

    Surface::sptr frame1 = video1->getFrame(frameNr);
    Surface::sptr frame2 = video2->getFrame(frameNr);

    GPUSurfaceShader gpuHelper(":/Shader/Diff/HSLPixelDiff.fs", frame1);

    gpuHelper.setValue("sourceTexture2", frame2);

    return Surface::sptr(gpuHelper.run());
}

Memento HSLPixelDiff::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}

    return PixelDiff::getMemento();
}

void HSLPixelDiff::restore(::model::saveable::Memento memento) {
    PixelDiff::restore(memento);
}

Saveable::sptr HSLPixelDiff::getDummy() {
    return HSLPixelDiff::sptr(new HSLPixelDiff());
}

HSLPixelDiff::HSLPixelDiff() : AveragePixelDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model