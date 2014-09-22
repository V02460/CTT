#include "HSLPixelDiff.h"

#include "GPUSurfaceShader.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::helper::GPUSurfaceShader;
using ::exception::AccessToDummyException;

const QByteArray HSLPixelDiff::kDiffID = QT_TRANSLATE_NOOP("Diff", "pixeldiff_hsl");

HSLPixelDiff::HSLPixelDiff(Video::sptr module1, Video::sptr module2) : AveragePixelDiff(module1, module2) {
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

    Surface::sptr frame1 = module1->getFrame(frameNr);
    Surface::sptr frame2 = module2->getFrame(frameNr);

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