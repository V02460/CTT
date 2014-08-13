#include "YUVDataVideo.h"

#include "NotImplementedException.h"
#include <QVector>
#include "MacroblockType.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::exception::IllegalArgumentException;
using ::model::frame::MacroblockType;
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
		if ((resolution.width() % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV422 format.");
		}
		chromaSize = pixelsPerFrame / 2;
		break;
	case YUV420:
		if ((resolution.width() % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels horizontally mustn't be in the YUV420 format.");
		}
		if ((resolution.height() % 2) != 0) {
			throw new IllegalArgumentException("A video with an uneven number of pixels vertically mustn't be in the YUV420 format.");
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

	if (((resolution.height() % 16) != 0) || ((resolution.width() % 16) != 0))
	{
		throw new IllegalArgumentException("The video of the submitted resolution " + QString::number(resolution.width()) + "x" 
			+ QString::number(resolution.height()) + "can't be divided into 16x16 pixel macroblocks, that means the metadata file containing macroblockmetadata can't make sense");
	}

	if (((pixelsPerFrame / 256) * metadata.getLength()) != metadataFile.size())
	{
		throw new IllegalArgumentException("The metadata file at the submitted location doesn't contain information about the number of macroblocks in the videofile (assuming 16x16p macroblocks and 1 byte of metadata per macroblock).");
}

	hasMetadataFile = true;

	loadMetadata(0);
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

	if (isDummy())
	{
		throw new NotImplementedException("Tried to request a frame from a dummy YUVDataVideo");
}

	if (!hasFrameInBuffer(frameNumber)) {
		load(frameNumber);
	}

	QImage image;

	QByteArray rawFrame = videoBuffer.mid((frameNumber - firstFrameInMemory) * bytesPerFrame, bytesPerFrame);
	//TODO fjdifrj imageFormat? mal kucken wies mit dem Indexed8 geht AAAAAAAHHHHH SHIT!
	image.loadFromData(rawFrame, "bmp");


	if (hasMetadataFile)
	{
		QByteArray rawMetadata = metadataBuffer.mid((frameNumber - firstFrameInMemory) * (pixelsPerFrame / 256), (pixelsPerFrame / 256));
		QVector<QVector<MacroblockType>> macroblockTypes(metadata.getSize().height() / 16);

		for (QVector<QVector<MacroblockType>>::iterator i = macroblockTypes.begin(); i != macroblockTypes.end(); i++)
		{
			i->resize(metadata.getSize().width() / 16);
		}
		//TODO WICHTIG sicherstellen dass das hier in der richtigen reihenfolge läuft, und nicht irgendwie gespiegelt zu den bildaten oder sowas, und das ganze testen natürlich, damit kein out of bounds zeug oder so läuft
		for (unsigned int i = 0; i < (pixelsPerFrame / 256); i++)
		{
			switch (rawMetadata[i])
			{
			case 0:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_SKIP;
				break;
			case 1:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_16X16;
				break;
			case 2:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_16X8;
				break;
			case 3:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_8X16;
				break;
			case 4:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_8X8;
				break;
			case 5:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_8X4;
				break;
			case 6:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_4X8;
				break;
			case 7:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_4X4;
				break;
			case 8:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTER_8X8_OR_BELOW;
				break;
			case 9:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTRA_4X4;
				break;
			case 10:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTRA_16X16;
				break;
			case 13:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTRA_8X8;
				break;
			case 14:
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::INTRA_PCM;
				break;
			default: 
				macroblockTypes[i / (metadata.getSize().width() / 16)][i % (metadata.getSize().width() / 16)] = MacroblockType::UNKNOWN;
			}
		}


	}

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
	//TODO eskjfe
    throw new NotImplementedException();
}

void YUVDataVideo::restore(Memento memento)
{
	//TODO kehflakf
    throw new NotImplementedException();
}

saveable::Saveable::SaveableType YUVDataVideo::getType() const {
	return Saveable::SaveableType::yUVDataVideo;
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
	if (!metadataFile.seek((pixelsPerFrame / 256) * startFrame)) {
		//TODO jgsgiruhs use IOException here
		//throw new IOException();
	}

	//TODO eufufe ordentliche größe statt bytesperframe
	metadataBuffer = metadataFile.read(numberOfFramesInMemory * (pixelsPerFrame / 256));

	metadataFile.close();
}

}  // namespace video
}  // namespace model