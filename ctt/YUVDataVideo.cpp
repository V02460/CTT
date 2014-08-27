#include "YUVDataVideo.h"

#include "NotImplementedException.h"
#include "MacroblockType.h"
#include "FileNotFoundException.h"
#include "IOException.h"
#include "FrameMetadata.h"
#include "GPUHelper.h"
#include "YUVType.h"
#include "GlobalContext.h"

namespace model {
namespace video {

using ::model::frame::Frame;
using ::helper::GPUHelper;
using ::model::frame::FrameMetadata;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
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

QVector<QRgb> YUVDataVideo::colorTable;

YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context)
	: FileVideo(pathToVideoFile, context)
	, metadata(resolution, framerate, 1)
	, pixelsPerFrame(resolution.height() * resolution.width())
	, type(type)
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
	default:
		throw new IllegalArgumentException("Submitted YUV type not supported.");
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

	if (YUVDataVideo::colorTable.isEmpty())
	{
		YUVDataVideo::colorTable.resize(256);
		QColor color;
		for (int i = 0; i < 256; i++)
		{
			color.setRgb(i, i, i);
			YUVDataVideo::colorTable[i] = color.rgb();
		}
	}

	isDummyFlag = false;
}

YUVDataVideo::YUVDataVideo(QString pathToVideoFile, QString pathToMetadataFile, QSize resolution, double framerate, YUVType type, QSharedPointer<QOpenGLContext> context)
	: YUVDataVideo(pathToVideoFile, resolution, framerate, type, context)

{
	this->pathToMetadataFile = pathToMetadataFile;
	metadataFile.setFileName(pathToMetadataFile);

	if (!metadataFile.exists())
	{
		throw new FileNotFoundException("The metadata file at \"" + pathToMetadataFile + "\" doesn't exist.");
	}

	if (((resolution.height() % 16) != 0) || ((resolution.width() % 16) != 0))
	{
		throw new IllegalArgumentException("The video of the submitted resolution " + QString::number(resolution.width()) + "x" 
			+ QString::number(resolution.height()) + "can't be divided into 16x16 pixel macroblocks, that means the metadata file containing macroblockmetadata can't make sense");
	}

	if (((pixelsPerFrame / 256) * metadata.getLength()) != metadataFile.size())
	{
		throw new IllegalArgumentException("The metadata file at the submitted location doesn't contain information about the exact number of macroblocks in the videofile (assuming 16x16p macroblocks and 1 byte of metadata per macroblock).");
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

model::frame::Frame::sptr YUVDataVideo::getFrame(unsigned int frameNumber) const 
{
	if (isDummy())
	{
		throw new NotImplementedException("Tried to request a frame from a dummy YUVDataVideo");
	}

	if (frameNumber >= getFrameCount())
	{
		throw new IllegalArgumentException("Tried to request frame " + QString::number(frameNumber) 
			+ " from a YUVDataVideo with only " + QString::number(getFrameCount()) + " frames.");
	}

	if (!hasFrameInBuffer(frameNumber)) {
		load(frameNumber);
	}

	QByteArray rawFrame(videoBuffer.mid((frameNumber - firstFrameInMemory) * bytesPerFrame, bytesPerFrame));

	QByteArray yChannel(rawFrame.left(pixelsPerFrame));
	QScopedPointer<QByteArray> uChannel;
	QScopedPointer<QByteArray> vChannel;

	QImage yImage(reinterpret_cast<const uchar*>(yChannel.constData()), getMetadata().getSize().width(), getMetadata().getSize().height(), QImage::Format_Indexed8);

	QScopedPointer<QImage> uImage;
	QScopedPointer<QImage> vImage;

	switch (type)
	{
	case YUV444:
		uChannel.reset(new QByteArray(rawFrame.mid(pixelsPerFrame, pixelsPerFrame)));
		vChannel.reset(new QByteArray(rawFrame.mid(2 * pixelsPerFrame, pixelsPerFrame)));
		uImage.reset(new QImage(reinterpret_cast<const uchar*>(uChannel->constData()), getMetadata().getSize().width(), getMetadata().getSize().height(), QImage::Format_Indexed8));
		vImage.reset(new QImage(reinterpret_cast<const uchar*>(vChannel->constData()), getMetadata().getSize().width(), getMetadata().getSize().height(), QImage::Format_Indexed8));
		break;
	case YUV422:
		uChannel.reset(new QByteArray(rawFrame.mid(pixelsPerFrame, pixelsPerFrame / 2)));
		vChannel.reset(new QByteArray(rawFrame.mid(pixelsPerFrame + (pixelsPerFrame / 2), pixelsPerFrame / 2)));
		uImage.reset(new QImage(reinterpret_cast<const uchar*>(uChannel->constData()), getMetadata().getSize().width() / 2, getMetadata().getSize().height(), QImage::Format_Indexed8));
		vImage.reset(new QImage(reinterpret_cast<const uchar*>(vChannel->constData()), getMetadata().getSize().width() / 2, getMetadata().getSize().height(), QImage::Format_Indexed8));
		break;
	case YUV420:
		uChannel.reset(new QByteArray(rawFrame.mid(pixelsPerFrame, pixelsPerFrame / 4)));
		vChannel.reset(new QByteArray(rawFrame.mid(pixelsPerFrame + (pixelsPerFrame / 4), pixelsPerFrame / 4)));
		uImage.reset(new QImage(reinterpret_cast<const uchar*>(uChannel->constData()), getMetadata().getSize().width() / 2, getMetadata().getSize().height() / 2, QImage::Format_Indexed8));
		vImage.reset(new QImage(reinterpret_cast<const uchar*>(vChannel->constData()), getMetadata().getSize().width() / 2, getMetadata().getSize().height() / 2, QImage::Format_Indexed8));
		break;
	default:
		throw new IllegalStateException("YUV type not supported.");
		break;
	}

	yImage.setColorTable(colorTable);
	uImage->setColorTable(colorTable);
	vImage->setColorTable(colorTable);

	yImage.save("C:/Users/Jonas/Downloads/ytestpic.bmp", "BMP");
	uImage->save("C:/Users/Jonas/Downloads/utestpic.bmp", "BMP");
	vImage->save("C:/Users/Jonas/Downloads/vtestpic.bmp", "BMP");

	Frame yFrame(context, yImage);
	Frame uFrame(context, *uImage);
	Frame vFrame(context, *vImage);

	GPUHelper::uptr myHelper;
	switch (type)
	{
	case YUV444:
		myHelper.reset(new GPUHelper(":/Shader/Conversion/YUV444toRGBsdtv.fs", context));
		break;
	case YUV422:
		myHelper.reset(new GPUHelper(":/Shader/Conversion/YUV422toRGBsdtv.fs", context));
		break;
	case YUV420:
		myHelper.reset(new GPUHelper(":/Shader/Conversion/YUV420toRGBsdtv.fs", context));
		break;
	default:
		throw new IllegalStateException("YUV type not supported.");
		break;
	}

	myHelper->setValue("uChannel", uFrame);
	myHelper->setValue("vChannel", vFrame);

	Surface::sptr resultSurface = myHelper->run(yFrame, getMetadata().getSize());

	Frame::sptr result;

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
		result.reset(new Frame(resultSurface, resultMetadata));
	}
	else
	{
		FrameMetadata resultMetadata(getMetadata().getSize());
		result.reset(new Frame(resultSurface, resultMetadata));
	}

	return result;
}


unsigned int YUVDataVideo::getFrameCount() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the frame count from a dummy YUVDataVideo.");
	}

	return metadata.getLength();
}


void YUVDataVideo::load(unsigned int startFrame) const
{
	if (startFrame >= getFrameCount())
	{
		throw new IllegalArgumentException("Tried to load a frame which isn't in the file.");
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
	return ((frameNr >= firstFrameInMemory) & (frameNr < (firstFrameInMemory + numberOfFramesInMemory))) 
		& (frameNr < metadata.getLength());
}

Memento YUVDataVideo::getMemento() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request a memento from a dummy YUVDataVideo.");
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

void YUVDataVideo::restore(Memento memento)
{
	context = GlobalContext::get();
	hasMetadataFile = false;

	pathToVideoFile = memento.getString(videoPathStringId);
	videoFile.setFileName(pathToVideoFile);

	if (!videoFile.exists())
	{
		throw new FileNotFoundException("The video file at \"" + pathToVideoFile + "\" doesn't exist");
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
	default:
		throw new IllegalArgumentException("Submitted YUV type not supported.");
	}


	bytesPerFrame = pixelsPerFrame + (2 * chromaSize);

	if ((videoFile.size() % bytesPerFrame) != 0)
	{
		throw new IllegalArgumentException("The size of the submitted video file (" + QString::number(videoFile.size())
			+ " bytes) isn't a multiple of the calculated frame size (" + QString::number(bytesPerFrame) + " bytes).");
	}
	unsigned int length = videoFile.size() / bytesPerFrame;

	metadata = VideoMetadata(resolution, memento.getDouble(framerateStringId), length);

	isDummyFlag = false;
	load(0);

	if (YUVDataVideo::colorTable.isEmpty())
	{
		YUVDataVideo::colorTable.resize(256);
		QColor color;
		for (int i = 0; i < 256; i++)
		{
			color.setRgb(i, i, i);
			YUVDataVideo::colorTable[i] = color.rgb();
		}
	}

	hasMetadataFile = memento.getBool(hasMetadataFileStringId);
	if (hasMetadataFile)
	{
		pathToMetadataFile = memento.getString(metadataPathStringId);
		metadataFile.setFileName(pathToMetadataFile);

		if (!metadataFile.exists())
		{
			throw new FileNotFoundException("The metadata file at \"" + pathToMetadataFile + "\" doesn't exist.");
		}

		if (((resolution.height() % 16) != 0) || ((resolution.width() % 16) != 0))
		{
			throw new IllegalArgumentException("The video of the submitted resolution " + QString::number(resolution.width()) + "x"
				+ QString::number(resolution.height()) + "can't be divided into 16x16 pixel macroblocks, that means the metadata file containing macroblockmetadata can't make sense");
		}

		if (((pixelsPerFrame / 256) * metadata.getLength()) != metadataFile.size())
		{
			throw new IllegalArgumentException("The metadata file at the submitted location doesn't contain information about the exact number of macroblocks in the videofile (assuming 16x16p macroblocks and 1 byte of metadata per macroblock).");
		}

		loadMetadata(0);
	}

	
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
		throw new IOException("Couldn't open the video file at \"" + pathToVideoFile + "\".");
	}
	if (!videoFile.seek(bytesPerFrame * startFrame)) {
		throw new IOException("Couldn't seek to " + QString::number(bytesPerFrame * startFrame) + " in the video file at \"" + pathToVideoFile + "\".");
	}

	unsigned int framesToLoad = numberOfFramesInMemory;

	if (getFrameCount() < (startFrame + numberOfFramesInMemory))
	{
		framesToLoad = getFrameCount() - startFrame;
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
		throw new IOException("Couldn't open the metadata file at \"" + pathToMetadataFile + "\".");
	}
	if (!metadataFile.seek((pixelsPerFrame / 256) * startFrame)) {
		throw new IOException("Couldn't seek to " + QString::number((pixelsPerFrame / 256) * startFrame) + " in the metadata file at \"" + pathToVideoFile + "\".");
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