#include "YUVPixelDiff.h"

#include "NotImplementedException.h"
#include "GPUHelper.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUHelper;

YUVPixelDiff::YUVPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
}

YUVPixelDiff::~YUVPixelDiff() {
}

Surface::sptr YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {
    throw new NotImplementedException();
    GPUHelper gpuHelper(":/Shader/Diff/yuvPixelDiff.fs", video1->getContext());

    gpuHelper.setValue("sourceTexture2", *video2->getFrame(frameNr).data());

    return Surface::sptr(gpuHelper.run(*video1->getFrame(frameNr).data()));
}

double YUVPixelDiff::getDiff(unsigned int frameNr) const {
    throw new NotImplementedException();

    Surface::sptr pixelDiff = getPixelDiff(frameNr);

    GPUHelper gpuHelper(":/Shader/compactAverage.fs", video1->getContext());
}

Memento YUVPixelDiff::getMemento() const {
    return PixelDiff::getMemento();
}

void YUVPixelDiff::restore(::model::saveable::Memento memento) {
    PixelDiff::restore(memento);
}

Saveable::sptr YUVPixelDiff::getDummy() {
    return YUVPixelDiff::sptr(new YUVPixelDiff());
}

Saveable::SaveableType YUVPixelDiff::getType() const {
	return Saveable::SaveableType::yUVPixelDiff;
}

YUVPixelDiff::YUVPixelDiff() : PixelDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model