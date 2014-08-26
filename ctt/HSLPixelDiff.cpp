#include "HSLPixelDiff.h"

#include "NotImplementedException.h"
#include "GPUHelper.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::helper::GPUHelper;
using ::exception::NotImplementedException;

HSLPixelDiff::HSLPixelDiff(Video::sptr video1, Video::sptr video2) : PixelDiff(video1, video2) {
    throw new NotImplementedException();
}

HSLPixelDiff::~HSLPixelDiff() {
    throw new NotImplementedException();
}

Surface::sptr HSLPixelDiff::getPixelDiff(unsigned int frameNr) const {
    throw new NotImplementedException();
    GPUHelper gpuHelper(":/Shader/Diff/hslPixelDiff.fs", video1->getContext());

    gpuHelper.setValue("sourceTexture2", *video2->getFrame(frameNr).data());

    return Surface::sptr(gpuHelper.run(*video1->getFrame(frameNr).data()));
}

double HSLPixelDiff::getDiff(unsigned int frameNr) const{
    throw new NotImplementedException();

    Surface::sptr pixelDiff = getPixelDiff(frameNr);

    GPUHelper gpuHelper(":/Shader/compactAverage.fs", video1->getContext());
}

Memento HSLPixelDiff::getMemento() const {
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