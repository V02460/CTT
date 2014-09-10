#include "Video.h"

#include "NotImplementedException.h"
#include "YUVType.h"
#include "IOException.h"
#include "GPUSurfaceShader.h"

#include <QFile>

namespace model {
namespace video {

using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;
using ::exception::IOException;
using ::model::saveable::Saveable;

using ::model::frame::Frame;
using model::filter::FilterParam;

model::filter::RescaleFilter::uptr Video::rescaler;

void Video::save(QString path, VideoFileType type) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}

	QFile videoFile(path);
	
	if (videoFile.exists())
	{
		videoFile.remove();
	}

	if (!videoFile.open(QIODevice::WriteOnly)) {
		throw IOException("Can't open the file at \"" + path + "\".");
	}

	QDataStream stream(&videoFile);

	//Currently only supports YUV444
	int bytesPerFrame = 3 * getResolution().width() * getResolution().height();

// 	switch (type)
// 	{
// 	case YUV444:
// 		bytesPerFrame = 3 * getResolution().width() * getResolution().height();
// 		break;
// 	case YUV422:
// 		if ((getResolution().width() % 2) != 0) {
// 			throw IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV422 format.");
// 		}
// 		bytesPerFrame = 2 * getResolution().width() * getResolution().height();
// 		break;
// 	case YUV420:
// 		if ((getResolution().width() % 2) != 0) {
// 			throw IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
// 		}
// 		if ((getResolution().height() % 2) != 0) {
// 			throw IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
// 		}
// 		bytesPerFrame = (3 * getResolution().width() * getResolution().height()) / 2;
// 		break;
// 	}

	helper::GPUSurfaceShader myHelper(":/Shader/Conversion/RGBtoYUV444sdtv.fs", getContext());
	for (unsigned int i = 0; i < getFrameCount(); i++)
	{
        myHelper.setSourceTexture(getFrame(i));
        Surface::sptr frame = myHelper.run();

		videoFile.write(frame->getRawRGBA().left(bytesPerFrame));
	}

	if (!videoFile.flush())
	{
		throw IOException("Can't flush the file at \"" + path + "\".");
	}
	
	videoFile.close();
}

::model::frame::Frame::sptr Video::getScaledFrame(Video::sptr video, unsigned int frameNumber, QSize size) {
    if (rescaler.isNull())
    {
		rescaler.reset(new model::filter::RescaleFilter(video));
	}
	else
	{
		rescaler->setPreviousModule(video);
	}

	FilterParam::sptr paramWidth(new FilterParam(model::filter::RescaleFilter::kParamNewSizeWidth, static_cast<unsigned int>(size.width())));
	rescaler->setParam(paramWidth);

    FilterParam::sptr paramHeight(new FilterParam(model::filter::RescaleFilter::kParamNewSizeHeight, static_cast<unsigned int>(size.height())));
    rescaler->setParam(paramHeight);

	return rescaler->getFrame(frameNumber);
}

QSize Video::getResolution() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return getMetadata().getSize();
}

}  // namespace video
}  // namespace model