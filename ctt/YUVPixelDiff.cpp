#include "YUVPixelDiff.h"

#include "GPUSurfaceShader.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;
using ::exception::AccessToDummyException;

YUVPixelDiff::YUVPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
}

YUVPixelDiff::~YUVPixelDiff() {
}

Surface::sptr YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();

    Surface::sptr frame1 = video1->getFrame(frameNr);
    Surface::sptr frame2 = video2->getFrame(frameNr);

    GPUSurfaceShader gpuHelper(":/Shader/Diff/yuvPixelDiff.fs", frame1);

    gpuHelper.setValue("sourceTexture2", frame2);

    return Surface::sptr(gpuHelper.run());
}

double YUVPixelDiff::getDiff(unsigned int frameNr) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    throw new NotImplementedException();

    Surface::sptr pixelDiff = getPixelDiff(frameNr);

    GPUSurfaceShader gpuHelper(":/Shader/compactAverage.fs", video1->getContext());
}

Memento YUVPixelDiff::getMemento() const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}

    return PixelDiff::getMemento();
}

void YUVPixelDiff::restore(::model::saveable::Memento memento) {
    PixelDiff::restore(memento);
}

Saveable::sptr YUVPixelDiff::getDummy() {
    return YUVPixelDiff::sptr(new YUVPixelDiff());
}

YUVPixelDiff::YUVPixelDiff() : PixelDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model