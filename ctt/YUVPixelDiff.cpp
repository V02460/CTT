#include "YUVPixelDiff.h"

#include "GPUSurfaceShader.h"
#include "GPUSurfaceCompactor.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfaceShader;
using ::helper::GPUSurfaceCompactor;
using ::helper::getNewSizeDefault;
using ::exception::AccessToDummyException;

const QByteArray YUVPixelDiff::kDiffID = QT_TRANSLATE_NOOP("PixelDiff", "pixeldiff_yuv");

YUVPixelDiff::YUVPixelDiff(Video::sptr video1, Video::sptr video2) : AveragePixelDiff(video1, video2) {
}

YUVPixelDiff::~YUVPixelDiff() {
}

Saveable::SaveableType YUVPixelDiff::saveableType() {
	return getSaveableType();
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

    Surface::sptr frame1 = video1->getFrame(frameNr);
    Surface::sptr frame2 = video2->getFrame(frameNr);

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