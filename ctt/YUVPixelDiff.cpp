#include "YUVPixelDiff.h"

#include "GPUSurfaceShader.h"
#include "GPUSurfaceCompactor.h"

namespace model {
namespace difference {

using ::model::Module;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;
using ::helper::GPUSurfaceCompactor;
using ::helper::getNewSizeDefault;
using ::exception::AccessToDummyException;

const QByteArray YUVPixelDiff::kDiffID = QT_TRANSLATE_NOOP("PixelDiff", "pixeldiff_yuv");

YUVPixelDiff::YUVPixelDiff(Module::sptr module1, Module::sptr module2) : AveragePixelDiff(module1, module2) {
}

YUVPixelDiff::~YUVPixelDiff() {
}

Surface::sptr YUVPixelDiff::getPixelDiff(unsigned int frameNr) const {
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

    GPUSurfaceShader gpuHelper(":/Shader/Diff/YUVPixelDiff.fs", frame1);

    gpuHelper.setValue("sourceTexture2", frame2);

    return Surface::sptr(gpuHelper.run());
}

Memento YUVPixelDiff::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}

    return PixelDiff::getMemento();
}

void YUVPixelDiff::restore(::model::saveable::Memento memento) {
    PixelDiff::restore(memento);
}

Saveable::sptr YUVPixelDiff::getDummy() {
    return YUVPixelDiff::sptr(new YUVPixelDiff());
}

YUVPixelDiff::YUVPixelDiff() : AveragePixelDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model