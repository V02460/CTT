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
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;
using ::exception::IllegalStateException;
using ::exception::IllegalArgumentException;
using ::model::frame::MacroblockType;
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
		: FileVideo(pathToVideoFile, context),
		  metadata(resolution, framerate, 1),
		  pixelsPerFrame(resolution.height() * resolution.width()),
		  type(type) {
	init(resolution, framerate);
}

void YUVDataVideo::init(QSize resolution, double framerate) {
	hasMetadataFile = false;

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

	isDummyFlag = false;
	load(0);

	isDummyFlag = false;
}

YUVDataVideo::YUVDataVideo(QString pathToVideoFile,
                           QString pathToMetadataFile,
                           QSize resolution,
                           double framerate,
                           YUVType type,
                           QSharedPointer<QOpenGLContext> context)
		: YUVDataVideo(pathToVideoFile, resolution, framerate, type, context) {
	initMetadata(pathToMetadataFile, resolution);
}

void YUVDataVideo::initMetadata(QString pathToMetadataFile, QSize resolution) {
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
            "that means the metadata file containing macroblockmetadata can't make sense");
	}

	if (((pixelsPerFrame / 256) * metadata.getLength()) != metadataFile.size())
	{
		throw IllegalArgumentException(
            "The metadata file at the submitted location doesn't contain information about the exact number of "
            "macroblocks in the videofile (assuming 16x16p macroblocks and 1 byte of metadata per macroblock).");
	}

	hasMetadataFile = true;

	loadMetadata(0);
}

YUVDataVideo::YUVDataVideo() : metadata(QSize(1, 1), 1, 1) {
	isDummyFlag = true;	
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

	if (!hasFrameInBuffer(frameNumber)) {
		load(frameNumber);
	}

    // BIG TODO: eliminate this awful hack
    GlobalContext::get();

	Frame::sptr result;

	if (hasMetadataFile)
	{
        QByteArray rawMetadata = metadataBuffer.mid((pixelsPerFrame / 256) * (frameNumber - firstFrameInMemory),
                                                    (pixelsPerFrame / 256));

		QVector<QVector<MacroblockType>> macroblockTypes(metadata.getSize().height() / 16);

		for (QVector<QVector<MacroblockType>>::iterator i = macroblockTypes.begin(); i != macroblockTypes.end(); i++)
		{
			i->resize(metadata.getSize().width() / 16);
		}
		//TODO WICHTIG sicherstellen dass das hier in der richtigen reihenfolge läuft
        //             und nicht irgendwie gespiegelt zu den bildaten oder sowas, und das ganze testen natürlich,
        //             damit kein out of bounds zeug oder so läuft
		for (unsigned int i = 0; i < (pixelsPerFrame / 256); i++)
		{
			int x = i / (metadata.getSize().width() / 16);
			int y = i % (metadata.getSize().width() / 16);

			switch (rawMetadata[i])
			{
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
		FrameMetadata resultMetadata(getMetadata().getSize(), macroblockTypes);
		result.reset(new Frame(videoBuffer[frameNumber - firstFrameInMemory], resultMetadata));
	}
	else
	{
		FrameMetadata resultMetadata(getMetadata().getSize());
		result.reset(new Frame(videoBuffer[frameNumber - firstFrameInMemory], resultMetadata));
	}

	return result;
}


unsigned int YUVDataVideo::getFrameCount() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return metadata.getLength();
}


void YUVDataVideo::load(unsigned int startFrame) const
{
	if (startFrame >= getFrameCount())
	{
		throw IllegalArgumentException("Tried to load a frame which isn't in the file.");
	}


	loadVideodata(startFrame);
	if (hasMetadataFile)
	{
		loadMetadata(startFrame);
	}
	firstFrameInMemory = startFrame;
}

bool YUVDataVideo::hasFrameInBuffer(unsigned int frameNr) const
{
	return (frameNr >= firstFrameInMemory) & 
           (frameNr < (firstFrameInMemory + numberOfFramesInMemory)) &
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
	// constuctor arguments
	QSize resolution(memento.getInt(resXStringId), memento.getInt(resYStringId));
	double framerate = memento.getDouble(framerateStringId);

	// FileVideo init list + constuctor
	pathToVideoFile = memento.getString(videoPathStringId);
	context = GlobalContext::get();
	videoFile.setFileName(pathToVideoFile);
	if (!videoFile.exists()) {
		throw FileNotFoundException("The video file at \"" + pathToVideoFile + "\" doesn't exist");
	}

	// init list + constructor
	metadata = VideoMetadata(resolution, framerate, 1);
	pixelsPerFrame = resolution.height() * resolution.width();
	type = static_cast<YUVType>(memento.getInt(yuvTypeStringId));
	init(resolution, framerate);
	if (memento.getBool(hasMetadataFileStringId)) {
		initMetadata(memento.getString(metadataPathStringId), resolution);
		}
}

Saveable::SaveableType YUVDataVideo::getSaveableType() {
    return Saveable::yUVDataVideo;
}

::model::saveable::Saveable::sptr YUVDataVideo::getDummy() {
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

	unsigned int framesToLoad = numberOfFramesInMemory;

	if (getFrameCount() < (startFrame + numberOfFramesInMemory))
	{
		framesToLoad = getFrameCount() - startFrame;
	}

	for (int i = 0; i < framesToLoad; i++)
	{
		char *yGPUBuffer;
		Surface::sptr yChannel(new Surface(context, getResolution(), &yGPUBuffer));
		videoFile.read(yGPUBuffer, pixelsPerFrame);

		char *uGPUBuffer;
		Surface::sptr uChannel;
		char *vGPUBuffer;
		Surface::sptr vChannel;

		switch (type)
		{
		case YUV444:
			uChannel.reset(new Surface(context, getResolution(), &uGPUBuffer, QOpenGLTexture::UInt8, QOpenGLTexture::Red, QOpenGLTexture::R8_UNorm));
			videoFile.read(uGPUBuffer, pixelsPerFrame);
			vChannel.reset(new Surface(context, getResolution(), &uGPUBuffer, QOpenGLTexture::UInt8, QOpenGLTexture::Red, QOpenGLTexture::R8_UNorm));
			videoFile.read(vGPUBuffer, pixelsPerFrame);
			break;
		case YUV422:
			uChannel.reset(new Surface(context, QSize(getResolution().width() / 2, getResolution().height()), &uGPUBuffer, QOpenGLTexture::UInt8, QOpenGLTexture::Red, QOpenGLTexture::R8_UNorm));
			videoFile.read(uGPUBuffer, pixelsPerFrame/2);
			vChannel.reset(new Surface(context, QSize(getResolution().width() / 2, getResolution().height()), &vGPUBuffer, QOpenGLTexture::UInt8, QOpenGLTexture::Red, QOpenGLTexture::R8_UNorm));
			videoFile.read(vGPUBuffer, pixelsPerFrame/2);
			break;
		case YUV420:
			uChannel.reset(new Surface(context, QSize(getResolution().width() / 2, getResolution().height() / 2), &uGPUBuffer, QOpenGLTexture::UInt8, QOpenGLTexture::Red, QOpenGLTexture::R8_UNorm));
			videoFile.read(uGPUBuffer, pixelsPerFrame / 4);
			vChannel.reset(new Surface(context, QSize(getResolution().width() / 2, getResolution().height() / 2), &vGPUBuffer, QOpenGLTexture::UInt8, QOpenGLTexture::Red, QOpenGLTexture::R8_UNorm));
			videoFile.read(vGPUBuffer, pixelsPerFrame / 4);
			break;
		default:
			throw IllegalStateException("YUV type not supported.");
			break;
		}

		yChannel->finishedTxtureUpload();
		uChannel->finishedTextureUpload();
		vChannel->finishedTextureUpload();

		GPUSurfaceShader::uptr converter;
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

		converter->setValue("uChannel", uChannel);
		converter->setValue("vChannel", uChannel);

		videoBuffer[i] = converter->run(getMetadata().getSize());
	}

	videoFile.close();
}

void YUVDataVideo::loadMetadata(unsigned int startFrame) const {
	if (!hasMetadataFile)
	{
		throw IllegalStateException("Tried to load metadata without having a metadata file.");
	}
	if (!metadataFile.open(QIODevice::ReadOnly)) {
		throw IOException("Couldn't open the metadata file at \"" + pathToMetadataFile + "\".");
	}
	if (!metadataFile.seek((pixelsPerFrame / 256) * startFrame)) {
		throw IOException("Couldn't seek to " +
                          QString::number((pixelsPerFrame / 256) * startFrame) +
                          " in the metadata file at \"" + pathToVideoFile + "\".");
	}

	unsigned int framesToLoad = numberOfFramesInMemory;

	if (getFrameCount() < (startFrame + numberOfFramesInMemory))
	{
		framesToLoad = getFrameCount() - startFrame;
	}

	metadataBuffer = metadataFile.read(framesToLoad * (pixelsPerFrame / 256));

	metadataFile.close();
}

}  // namespace video
}  // namespace model