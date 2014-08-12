#include "YUVDataVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::exception::IllegalArgumentException;
//using ::exception::IOException;


YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context)
	: FileVideo(pathToVideoFile, context)
	, metadata(resolution, framerate, 1)
	, pixelsPerFrame(resolution.height() * resolution.width())
{
	hasMetadataFile = false;

	switch (type)
	{
	case YUV444:
		chromaSize = pixelsPerFrame;
		break;
	case YUV422:
		if ((pixelsPerFrame % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels per frame mustn't be in the YUV422 format.");
		}
		chromaSize = pixelsPerFrame / 2;
		break;
	case YUV420:
		if ((pixelsPerFrame % 2) != 0) {
			throw new IllegalArgumentException("A video with number of pixels per frame which isn't a multiple of 4 mustn't be in the YUV420 format.");
		}
		chromaSize = pixelsPerFrame / 4;
		break;
	}

	bytesPerFrame = pixelsPerFrame + (2 * chromaSize);

	if ((videoFile.size() % bytesPerFrame) != 0)
	{
		throw new IllegalArgumentException("The size of the submitted video file (" + QString::number(videoFile.size())
			+ " bytes) isn't a multiple of the calculated frame size (" + QString::number(bytesPerFrame) + " bytes).");
	}
	unsigned int length = videoFile.size() / bytesPerFrame;

	metadata = VideoMetadata(resolution, framerate, length);

	load(0);
}

YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context)
	: YUVDataVideo(pathToVideoFile, resolution, framerate, type, context)

{
	this->pathToMetadataFile = pathToMetadataFile;
	metadataFile.setFileName(pathToMetadataFile);

	if (!metadataFile.exists())
	{
		//TODO use the File not found exception jeshgni
		//throw new FileNotFoundException();
	}

	hasMetadataFile = true;

	load(0);	//now with metadatafile stuff
}

YUVDataVideo::YUVDataVideo()
	:metadata(QSize(1, 1), 1, 1)
{
	isDummyFlag = true;	
}


YUVDataVideo::~YUVDataVideo() {

}

VideoMetadata YUVDataVideo::getMetadata() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request metadata from a dummy YUVDataVideo.");
	}

	return metadata;
}

model::frame::Frame::sptr YUVDataVideo::getFrame(unsigned int frameNumber) const {
	throw new NotImplementedException();

	if (!hasFrameInBuffer(frameNumber)) {
		load(frameNumber);
	}

	QImage image;

	QByteArray rawFrame = videoBuffer.mid((frameNumber - firstFrameInMemory) * bytesPerFrame, bytesPerFrame);
	//TODO fjdifrj imageFormat? mal kucken wies mit dem Indexed8 geht AAAAAAAHHHHH SHIT!
	image.loadFromData(rawFrame, "bmp");

}

QList<const Module*> YUVDataVideo::getUsesList() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request a list of used modules from a dummy YUVDataVideo.");
	}

	QList<const Module*> uses;
	uses.append(this);

	return uses;
}

unsigned int YUVDataVideo::getFrameCount() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the frame count from a dummy YUVDataVideo.");
	}

	return metadata.getLength();
}

bool YUVDataVideo::uses(const model::Module &module) const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to ask a dummy YUVDataVideo whether it used a specific module.");
	}

	return (this == &module);
}

void YUVDataVideo::load(unsigned int startFrame) const
{
	loadVideodata(pixelsPerFrame);

	if (hasMetadataFile)
	{
		loadMetadata(startFrame);
	}

	firstFrameInMemory = startFrame;
}

bool YUVDataVideo::hasFrameInBuffer(unsigned int frameNr) const
{
	return ((frameNr >= firstFrameInMemory) & (frameNr < (firstFrameInMemory + numberOfFramesInMemory))) 
		& (frameNr < metadata.getLength());
}

Memento YUVDataVideo::getMemento() const
{
	throw new NotImplementedException();
}

void YUVDataVideo::restore(Memento memento)
{
	throw new NotImplementedException();
}

::model::saveable::Saveable::sptr YUVDataVideo::getDummy()
{
	return YUVDataVideo::sptr(new YUVDataVideo);
}

void YUVDataVideo::loadVideodata(unsigned int startFrame) const
{

	if (!videoFile.open(QIODevice::ReadOnly)) {
		//TODO jgsgiruhs use IOException here
		//throw new IOException();
	}
	if (!videoFile.seek(bytesPerFrame * startFrame)) {
		//TODO jgsgiruhs use IOException here
		//throw new IOException();
	}

	videoBuffer = videoFile.read(numberOfFramesInMemory * bytesPerFrame);

	videoFile.close();
}

void YUVDataVideo::loadMetadata(unsigned int startFrame) const
{
	if (!hasMetadataFile)
	{
		throw new IllegalStateException("Tried to load metadata without having a metadata file.");
	}
	if (!metadataFile.open(QIODevice::ReadOnly)) {
		//TODO jgsgiruhs use IOException here
		//throw new IOException();
	}
	if (!metadataFile.seek(bytesPerFrame * startFrame)) {
		//TODO jgsgiruhs use IOException here
		//throw new IOException();
	}

	metadataBuffer = metadataFile.read(numberOfFramesInMemory * bytesPerFrame);

	metadataFile.close();
}

}  // namespace video
}  // namespace model