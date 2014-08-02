#include "YUVDataVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
//using ::exception::IOException;

YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context)
	: FileVideo(pathToVideoFile, context)
	, pathToMetadataFile(pathToMetadataFile)
	, metadataFile(pathToMetadataFile)
	, metadataFileStream(&metadataFile)
	//TODO rjdhgdd initialize length here already?
	, metadata(resolution, framerate, 1)
	, pixelsPerFrame(resolution.height() * resolution.width())
{
	if (!metadataFile.exists())
	{
		//TODO use the File not found exception jeshgni
		//throw new FileNotFoundException();
	}

	switch (type)
	{
	case YUV444:
		chromaSize = pixelsPerFrame;
		break;
	case YUV422:
		chromaSize = pixelsPerFrame / 2;
		break;
	case YUV420:
		chromaSize = pixelsPerFrame / 4;
		break;
	}

	bytesPerFrame = pixelsPerFrame + (2 * chromaSize);

	unsigned int length = videoFile.size() / bytesPerFrame;

	metadata = VideoMetadata(resolution, framerate, length);

	load(0);
}

YUVDataVideo::~YUVDataVideo() {
	isDummyFlag = true;
}

VideoMetadata YUVDataVideo::getMetadata() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request metadata from a dummy YUVDataVideo.");
	}

	return metadata;
}

model::frame::Frame::sptr YUVDataVideo::getFrame(unsigned int frameNumber) const {
	throw new NotImplementedException();
// 	if (!hasFrameInBuffer(frameNumber)) {
// 		load(frameNumber);
// 	}

	//QImage image();

	//TODO fjdifrj imageFormat?
	//image.loadFromData(videoBuffer.mid(1, 1), QImage::Format_RGB888);
}

QList<Module*> YUVDataVideo::getUsesList()
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request a list of used modules from a dummy YUVDataVideo.");
	}

	QList<Module*> uses;
	uses.append(this);

	return uses;
}

unsigned int YUVDataVideo::getFrameCount()
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the frame count from a dummy YUVDataVideo.");
	}

	return metadata.getLength();
}

bool YUVDataVideo::uses(const model::Module &module)
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to ask a dummy YUVDataVideo whether it used a specific moduke.");
	}

	return (this == &module);
}

void YUVDataVideo::load(unsigned int startFrame) const
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

	firstFrameInMemory = startFrame;
}

bool YUVDataVideo::hasFrameInBuffer(unsigned int frameNr) const
{
	return ((frameNr >= firstFrameInMemory) & (frameNr < (firstFrameInMemory + numberOfFramesInMemory))) 
		& (frameNr < metadata.getLength());
}

}  // namespace video
}  // namespace model