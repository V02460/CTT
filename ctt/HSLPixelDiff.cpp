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

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    throw new NotImplementedException();
}

HSLPixelDiff::~HSLPixelDiff() {
    throw new NotImplementedException();
}

Surface::sptr HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();
    
    Surface::sptr frame1 = video1->getFrame(frameNr);
    Surface::sptr frame2 = video2->getFrame(frameNr);

    GPUSurfaceShader gpuHelper(":/Shader/Diff/hslPixelDiff.fs", frame1);

    gpuHelper.setValue("sourceTexture2", frame2);

    return Surface::sptr(gpuHelper.run());
}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();

    Surface::sptr frame1 = video1->getFrame(frameNr);

    Surface::sptr pixelDiff = getPixelDiff(frameNr);

    GPUSurfaceShader gpuHelper(":/Shader/compactAverage.fs", frame1);
}

Memento HSLPixelDiff::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}

    return PixelDiff::getMemento();
}

void HSLPixelDiff::restore(::model::saveable::Memento memento) {
    PixelDiff::restore(memento);
}

Saveable::sptr HSLPixelDiff::getDummy() {
    return HSLPixelDiff::sptr(new HSLPixelDiff());
}

HSLPixelDiff::HSLPixelDiff() : PixelDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model