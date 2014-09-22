#include "AveragePixelDiff.h"

#include "AccessToDummyException.h"
#include "GPUSurfaceCompactor.h"

namespace model {
namespace difference {

using ::model::video::Video;
using ::helper::GPUSurfaceCompactor;
using ::helper::getNewSizeDefault;
using ::exception::AccessToDummyException;

AveragePixelDiff::AveragePixelDiff(Module::sptr module1, Module::sptr module2) : PixelDiff(module1, module2) {}

AveragePixelDiff::~AveragePixelDiff() {
}

double AveragePixelDiff::getDiff(unsigned int frameNr) {
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
	if (!isCalculated) {
		update();
	}

    return diff.value(frameNr);
}

void AveragePixelDiff::calculateFrameDiff(unsigned int frameNr) {
	Surface::sptr pixelDiff = getPixelDiff(frameNr);

	GPUSurfaceCompactor compactor(":/Shader/CompactAverage.fs", pixelDiff, getNewSizeDefault);
	Surface::sptr compactionResult = compactor.run(QSize(16, 16));

	QByteArray rawValues = compactionResult->getRawRGBA();

	// unpack the 16x16 texture with a single float saved in each rgba pixel
	float result = 0;
	for (unsigned int i = 0; i < 256; i++) {
		char r = rawValues[4 * i];
		char g = rawValues[4 * i + 1];
		char b = rawValues[4 * i + 2];
		char a = rawValues[4 * i + 3];

		result += reinterpret_cast<unsigned char&>(r) / 255.f
			+ reinterpret_cast<unsigned char&>(g) / 65025.f
			+ reinterpret_cast<unsigned char&>(b) / 16581375.f
			+ reinterpret_cast<unsigned char&>(a) / 4228250625.f;
	}

	diff.insert(frameNr, result / 256);
}

AveragePixelDiff::AveragePixelDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model