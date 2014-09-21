#include "YUVDataVideo.h"

#include "NotImplementedException.h"
#include "MacroblockType.h"
#include "FileNotFoundException.h"
#include "IOException.h"
#include "FrameMetadata.h"
#include "GPUSurfaceShader.h"
#include "YUVType.h"
#include "GlobalContext.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::helper::GPUSurfaceShader;
using ::model::frame::FrameMetadata;
using ::model::saveable::Saveable;
using ::model::frame::MacroblockType;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;
using ::exception::IllegalStateException;
using ::exception::IllegalArgumentException;
using ::exception::IOException;
using ::exception::FileNotFoundException;

const QString YUVDataVideo::hasMetadataFileStringId = "hasMetadata";
const QString YUVDataVideo::resXStringId = "resX";
const QString YUVDataVideo::resYStringId = "resY";
const QString YUVDataVideo::videoPathStringId = "vidPath";
const QString YUVDataVideo::metadataPathStringId = "metaPath";
const QString YUVDataVideo::framerateStringId = "framerate";
const QString YUVDataVideo::yuvTypeStringId = "yuvtype";

YUVDataVideo::YUVDataVideo(QString pathToVideoFile,
                           QSize resolution,
                           double framerate,
                           YUVType type,
                           QSharedPointer<QOpenGLContext> context)
						   : YUVDataVideo(pathToVideoFile, resolution, framerate, type, false, context)
{

}

YUVDataVideo::YUVDataVideo(QString pathToVideoFile,
                           QString pathToMetadataFile,
                           QSize resolution,
                           double framerate,
                           YUVType type,
                           QSharedPointer<QOpenGLContext> context)
	    : YUVDataVideo(pathToVideoFile, pathToMetadataFile, resolution, framerate, type, false, context)
{
	
}

YUVDataVideo::YUVDataVideo() : metadata(QSize(1, 1), 1, 1) {
	isDummyFlag = true;
}

YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QSize resolution, double framerate, YUVType type, bool isHDTV, QSharedPointer<QOpenGLContext> context)
	: FileVideo(pathToVideoFile, GlobalContext::get())
	, metadata(resolution, framerate, 1)
	, pixelsPerFrame(resolution.height() * resolution.width())
	, type(type)
	, isHDTV(isHDTV)
	, videoSurfaceBuffer(kNumberOfFramesInMemory)
	, videoBuffer(kNumberOfFramesInMemory)
	, metadataBuffer(kNumberOfFramesInMemory)
	, hasMetadataFile(false) {

	switch (type)
	{
	case YUV444:
		chromaSize = pixelsPerFrame;
		break;
	case YUV422:
		if ((resolution.width() % 2) != 0) {
			throw IllegalArgumentException(
				"A video with an uneven number of pixels horizontally mustn't be in the YUV422 format.");
		}
		chromaSize = pixelsPerFrame / 2;
		break;
	case YUV420:
		if ((resolution.width() % 2) != 0) {
			throw IllegalArgumentException(
				"A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
		}
		if ((resolution.height() % 2) != 0) {
			throw IllegalArgumentException(
				"A video with an uneven number of pixels vertically mustn't be in the YUV420 format.");
		}
		chromaSize = pixelsPerFrame / 4;
		break;
	default:
		throw IllegalArgumentException("Submitted YUV type not supported.");
	}

	bytesPerFrame = pixelsPerFrame + (2 * chromaSize);

	if ((videoFile.size() % bytesPerFrame) != 0)
	{
		throw IllegalArgumentException("The size of the submitted video file (" + QString::number(videoFile.size())
			+ " bytes) isn't a multiple of the calculated frame size (" + QString::number(bytesPerFrame) + " bytes).");
	}
	unsigned int length = videoFile.size() / bytesPerFrame;

	metadata = VideoMetadata(resolution, framerate, length);

	load(0);
}

YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, bool isHDTV, QSharedPointer<QOpenGLContext> context)
	: YUVDataVideo(pathToVideoFile, resolution, framerate, type, isHDTV, context)
{
	this->pathToMetadataFile = pathToMetadataFile;
	metadataFile.setFileName(pathToMetadataFile);

	if (!metadataFile.exists())
	{
		throw FileNotFoundException("The metadata file at \"" + pathToMetadataFile + "\" doesn't exist.");
	}

	if (((resolution.height() % 16) != 0) || ((resolution.width() % 16) != 0))
	{
		throw IllegalArgumentException(
			"The video of the submitted resolution " +
			QString::number(resolution.width()) + "x" + QString::number(resolution.height()) +
			"can't be divided into 16x16 pixel macroblocks, "
			"that means the metadata file containing macroblock metadata can't make sense");
	}

	if (((pixelsPerFrame / 256) * metadata.getLength()) != metadataFile.size())
	{
		throw IllegalArgumentException(
			"The metadata file at the submitted location doesn't contain information about the exact number of "
			"macroblocks in the video file (assuming 16x16p macroblocks and 1 byte of metadata per macroblock).");
	}

	hasMetadataFile = true;

	loadMetadata(0);

	// implant loaded metadata to frames
	for (unsigned int i = 0; i < getFramesToLoad(firstFrameInMemory); i++) {
		videoBuffer[i] = Frame::sptr(new Frame(videoBuffer[i].staticCast<Surface>(), *metadataBuffer[i]));
	}
}

YUVDataVideo::~YUVDataVideo() {
}

VideoMetadata YUVDataVideo::getMetadata() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return metadata;
}

model::frame::Frame::sptr YUVDataVideo::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (frameNumber >= getFrameCount())
	{
		throw IllegalArgumentException("Tried to request frame " + QString::number(frameNumber) 
			+ " from a YUVDataVideo with only " + QString::number(getFrameCount()) + " frames.");
	}

    // BIG TODO: eliminate this awful hack
    GlobalContext::get();

	if (!hasFrameInBuffer(frameNumber)) {
		load(frameNumber);
	}

    return videoBuffer[frameNumber - firstFrameInMemory];
}

unsigned int YUVDataVideo::getFrameCount() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return metadata.getLength();
}

void YUVDataVideo::load(unsigned int startFrame) const {
	if (startFrame >= getFrameCount()) {
		throw IllegalArgumentException("Tried to load a frame which isn't in the file.");
	}

	loadVideodata(startFrame);
    loadMetadata(startFrame);

    for (unsigned int i = 0; i < getFramesToLoad(startFrame); i++) {
        videoBuffer[i] = Frame::sptr(new Frame(videoSurfaceBuffer[i], *metadataBuffer[i]));
        videoSurfaceBuffer[i].reset(); // get rid of the old Surface, so we don't have an undefined state
    }

	firstFrameInMemory = startFrame;
}

bool YUVDataVideo::hasFrameInBuffer(unsigned int frameNr) const {
	return (frameNr >= firstFrameInMemory) & 
           (frameNr < (firstFrameInMemory + kNumberOfFramesInMemory)) &
		    (frameNr < metadata.getLength());
}

Memento YUVDataVideo::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;

	memento.setBool(hasMetadataFileStringId, hasMetadataFile);
	if (hasMetadataFile)
	{
		memento.setString(metadataPathStringId, pathToMetadataFile);
	}

	memento.setInt(resXStringId, getResolution().width());
	memento.setInt(resYStringId, getResolution().height());

	memento.setString(videoPathStringId, pathToVideoFile);

	memento.setDouble(framerateStringId, getMetadata().getFPS());

	memento.setInt(yuvTypeStringId, type);

	return memento;
}

void YUVDataVideo::restore(Memento memento) {
	context = GlobalContext::get();
	hasMetadataFile = false;

	pathToVideoFile = memento.getString(videoPathStringId);
	videoFile.setFileName(pathToVideoFile);

	if (!videoFile.exists()) {
		throw FileNotFoundException("The video file at \"" + pathToVideoFile + "\" doesn't exist");
	}

	QSize resolution(memento.getInt(resXStringId), memento.getInt(resYStringId));
	pixelsPerFrame = resolution.height() * resolution.width();
	type = static_cast<YUVType>(memento.getInt(yuvTypeStringId));

	switch (type)
	{
	case YUV444:
		chromaSize = pixelsPerFrame;
		break;
	case YUV422:
		if ((resolution.width() % 2) != 0) {
			throw IllegalArgumentException(
                "A video with an uneven number of pixels horizontally mustn't be in the YUV422 format.");
		}
		chromaSize = pixelsPerFrame / 2;
		break;
	case YUV420:
		if ((resolution.width() % 2) != 0) {
			throw IllegalArgumentException(
                "A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
		}
		if ((resolution.height() % 2) != 0) {
			throw IllegalArgumentException(
                "A video with an uneven number of pixels vertically mustn't be in the YUV420 format.");
		}
		chromaSize = pixelsPerFrame / 4;
		break;
	default:
		throw IllegalArgumentException("Submitted YUV type not supported.");
	}


	bytesPerFrame = pixelsPerFrame + (2 * chromaSize);

	if ((videoFile.size() % bytesPerFrame) != 0) {
		throw IllegalArgumentException("The size of the submitted video file (" + QString::number(videoFile.size())
			+ " bytes) isn't a multiple of the calculated frame size (" + QString::number(bytesPerFrame) + " bytes).");
	}
	unsigned int length = videoFile.size() / bytesPerFrame;

	metadata = VideoMetadata(resolution, memento.getDouble(framerateStringId), length);

	isDummyFlag = false;

    videoSurfaceBuffer.resize(kNumberOfFramesInMemory);
    videoBuffer.resize(kNumberOfFramesInMemory);
    metadataBuffer.resize(kNumberOfFramesInMemory);

	hasMetadataFile = memento.getBool(hasMetadataFileStringId);
	if (hasMetadataFile)
	{
		pathToMetadataFile = memento.getString(metadataPathStringId);
		metadataFile.setFileName(pathToMetadataFile);

		if (!metadataFile.exists())
		{
			throw FileNotFoundException("The metadata file at \"" + pathToMetadataFile + "\" doesn't exist.");
		}

		if (((resolution.height() % 16) != 0) || ((resolution.width() % 16) != 0))
		{
			throw IllegalArgumentException(
                "The video of the submitted resolution " +
                QString::number(resolution.width()) + "x" + QString::number(resolution.height()) +
                "can't be divided into 16x16 pixel macroblocks, "
                "that means the metadata file containing macroblock metadata can't make sense");
		}

		if (((pixelsPerFrame / 256) * metadata.getLength()) != metadataFile.size())
		{
			throw IllegalArgumentException(
                "The metadata file at the submitted location doesn't contain information about the exact number of "
                "macroblocks in the video file (assuming 16x16p macroblocks and 1 byte of metadata per macroblock).");
		}
	}

    load(0);
}

Saveable::SaveableType YUVDataVideo::getSaveableType() {
    return Saveable::yUVDataVideo;
}

Saveable::sptr YUVDataVideo::getDummy() {
	return YUVDataVideo::sptr(new YUVDataVideo);
}

void YUVDataVideo::loadVideodata(unsigned int startFrame) const {
	if (!videoFile.open(QIODevice::ReadOnly)) {
		throw IOException("Couldn't open the video file at \"" + pathToVideoFile + "\".");
	}
	if (!videoFile.seek(bytesPerFrame * startFrame)) {
		throw IOException("Couldn't seek to " +
                          QString::number(bytesPerFrame * startFrame) +
                          " in the video file at \"" + pathToVideoFile + "\".");
	}

    GlobalContext::get();

    for (unsigned int i = 0; i < getFramesToLoad(startFrame); i++) {
		char *yGPUBuffer;
        Surface::sptr yChannel(new Surface(context,
                                           getResolution(),
                                           reinterpret_cast<void**>(&yGPUBuffer),
                                           QOpenGLTexture::UInt8,
                                           QOpenGLTexture::Red,
                                           QOpenGLTexture::R8_UNorm));
		videoFile.read(yGPUBuffer, pixelsPerFrame);

		char *uGPUBuffer;
		Surface::sptr uChannel;
		char *vGPUBuffer;
		Surface::sptr vChannel;

		switch (type)
		{
		case YUV444:
			uChannel.reset(new Surface(context,
                                       getResolution(),
                                       reinterpret_cast<void**>(&uGPUBuffer),
                                       QOpenGLTexture::UInt8,
                                       QOpenGLTexture::Red,
                                       QOpenGLTexture::R8_UNorm));
			videoFile.read(uGPUBuffer, pixelsPerFrame);

			vChannel.reset(new Surface(context,
                                       getResolution(),
                                       reinterpret_cast<void**>(&vGPUBuffer),
                                       QOpenGLTexture::UInt8,
                                       QOpenGLTexture::Red,
                                       QOpenGLTexture::R8_UNorm));
			videoFile.read(vGPUBuffer, pixelsPerFrame);
			break;
		case YUV422:
			uChannel.reset(new Surface(context,
                                       QSize(getResolution().width() / 2, getResolution().height()),
                                       reinterpret_cast<void**>(&uGPUBuffer),
                                       QOpenGLTexture::UInt8,
                                       QOpenGLTexture::Red,
                                       QOpenGLTexture::R8_UNorm));
			videoFile.read(uGPUBuffer, pixelsPerFrame/2);

			vChannel.reset(new Surface(context,
                                       QSize(getResolution().width() / 2, getResolution().height()),
                                       reinterpret_cast<void**>(&vGPUBuffer),
                                       QOpenGLTexture::UInt8,
                                       QOpenGLTexture::Red,
                                       QOpenGLTexture::R8_UNorm));
			videoFile.read(vGPUBuffer, pixelsPerFrame/2);

			break;
		case YUV420:
			uChannel.reset(new Surface(context,
                                       QSize(getResolution().width() / 2, getResolution().height() / 2),
                                       reinterpret_cast<void**>(&uGPUBuffer),
                                       QOpenGLTexture::UInt8,
                                       QOpenGLTexture::Red,
                                       QOpenGLTexture::R8_UNorm));
			videoFile.read(uGPUBuffer, pixelsPerFrame / 4);

			vChannel.reset(new Surface(context,
                                       QSize(getResolution().width() / 2, getResolution().height() / 2),
                                       reinterpret_cast<void**>(&vGPUBuffer),
                                       QOpenGLTexture::UInt8,
                                       QOpenGLTexture::Red,
                                       QOpenGLTexture::R8_UNorm));
			videoFile.read(vGPUBuffer, pixelsPerFrame / 4);
			break;
		default:
			throw IllegalStateException("YUV type not supported.");
			break;
		}

		yChannel->finishTextureUpload();
        uChannel->finishTextureUpload();
        vChannel->finishTextureUpload();

		GPUSurfaceShader::uptr converter;

		if (!isHDTV)
		{
			switch (type)
			{
			case YUV444:
				converter.reset(new GPUSurfaceShader(":/Shader/Conversion/YUV444toRGBsdtv.fs", yChannel));
				break;
			case YUV422:
				converter.reset(new GPUSurfaceShader(":/Shader/Conversion/YUV422toRGBsdtv.fs", yChannel));
				break;
			case YUV420:
				converter.reset(new GPUSurfaceShader(":/Shader/Conversion/YUV420toRGBsdtv.fs", yChannel));
				break;
			default:
				throw IllegalStateException("YUV type not supported.");
				break;
			}
		}
		else
		{
			switch (type)
			{
			case YUV444:
				converter.reset(new GPUSurfaceShader(":/Shader/Conversion/YUV444toRGBhdtv.fs", yChannel));
				break;
			case YUV422:
				converter.reset(new GPUSurfaceShader(":/Shader/Conversion/YUV422toRGBhdtv.fs", yChannel));
				break;
			case YUV420:
				converter.reset(new GPUSurfaceShader(":/Shader/Conversion/YUV420toRGBhdtv.fs", yChannel));
				break;
			default:
				throw IllegalStateException("YUV type not supported.");
				break;
			}
		}
		

		converter->setValue("uChannel", uChannel);
		converter->setValue("vChannel", vChannel);

        converter->invertY(true);

        Surface::sptr loadedFrame = converter->run(getMetadata().getSize());

        //loadedFrame->getFramebufferObject()->toImage().save("E:/Projects/Encoder Analyzer/CTT/image.png");

        videoSurfaceBuffer[i] = loadedFrame;
	}

	videoFile.close();
}

void YUVDataVideo::loadMetadata(unsigned int startFrame) const {
    unsigned int framesToLoad = getFramesToLoad(startFrame);

	if (!hasMetadataFile) {
        FrameMetadata::sptr defaultFrameMetadata(new FrameMetadata(metadata.getSize()));
        for (unsigned int i = 0; i < framesToLoad; i++) {
            metadataBuffer[i] = defaultFrameMetadata;
        }
        return;
	}

	if (!metadataFile.open(QIODevice::ReadOnly)) {
		throw IOException("Couldn't open the metadata file at \"" + pathToMetadataFile + "\".");
	}
	if (!metadataFile.seek((pixelsPerFrame / 256) * startFrame)) {
		throw IOException("Couldn't seek to " +
                          QString::number((pixelsPerFrame / 256) * startFrame) +
                          " in the metadata file at \"" + pathToVideoFile + "\".");
	}

    QByteArray rawMetadata = metadataFile.read(framesToLoad * (pixelsPerFrame / 256));

	metadataFile.close();

    // extract the metadata for every loaded frame
    for (unsigned int j = 0; j < framesToLoad; j++) {

        QByteArray rawFrameMetadata = rawMetadata.mid((pixelsPerFrame / 256) * j,
                                                      (pixelsPerFrame / 256));

        QVector<QVector<MacroblockType>> macroblockTypes(metadata.getSize().height() / 16);

        // allocate space for the multidimensional array
        for (auto i = macroblockTypes.begin(); i != macroblockTypes.end(); i++) {
            i->resize(metadata.getSize().width() / 16);
        }

        // get the type for every macroblock in the frame
        for (unsigned int i = 0; i < (pixelsPerFrame / 256); i++) {
            int x = i / (metadata.getSize().width() / 16);
            int y = i % (metadata.getSize().width() / 16);

            switch (rawFrameMetadata[i]) {
                case 0:
                    macroblockTypes[x][y] = MacroblockType::INTER_SKIP;
                    break;
                case 1:
                    macroblockTypes[x][y] = MacroblockType::INTER_16X16;
                    break;
                case 2:
                    macroblockTypes[x][y] = MacroblockType::INTER_16X8;
                    break;
                case 3:
                    macroblockTypes[x][y] = MacroblockType::INTER_8X16;
                    break;
                case 4:
                    macroblockTypes[x][y] = MacroblockType::INTER_8X8;
                    break;
                case 5:
                    macroblockTypes[x][y] = MacroblockType::INTER_8X4;
                    break;
                case 6:
                    macroblockTypes[x][y] = MacroblockType::INTER_4X8;
                    break;
                case 7:
                    macroblockTypes[x][y] = MacroblockType::INTER_4X4;
                    break;
                case 8:
                    macroblockTypes[x][y] = MacroblockType::INTER_8X8_OR_BELOW;
                    break;
                case 9:
                    macroblockTypes[x][y] = MacroblockType::INTRA_4X4;
                    break;
                case 10:
                    macroblockTypes[x][y] = MacroblockType::INTRA_16X16;
                    break;
                case 13:
                    macroblockTypes[x][y] = MacroblockType::INTRA_8X8;
                    break;
                case 14:
                    macroblockTypes[x][y] = MacroblockType::INTRA_PCM;
                    break;
                default:
                    macroblockTypes[x][y] = MacroblockType::UNKNOWN;
            }
        }

        metadataBuffer[j] = FrameMetadata::sptr(new FrameMetadata(getMetadata().getSize(), macroblockTypes));
    }
}

unsigned int YUVDataVideo::getFramesToLoad(unsigned int startFrame) const {
    unsigned int framesToLoad = kNumberOfFramesInMemory;

    if (getFrameCount() < (startFrame + kNumberOfFramesInMemory)) {
        framesToLoad = getFrameCount() - startFrame;
    }

    return framesToLoad;
}

}  // namespace video
}  // namespace model