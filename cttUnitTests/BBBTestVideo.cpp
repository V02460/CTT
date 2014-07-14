#include "BBBTestVideo.h"

#include "Module.h"

#include "NotImplementedException.h"

using exception::NotImplementedException;

BBBTestVideo::BBBTestVideo(unsigned int frameCount) : metadata(QSize(640, 360), 24, frameCount)
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();

	QImage testImage;

	for (unsigned int i = 1; i <= frameCount; i++)
	{
		QString numberString;
		numberString.setNum(i);
		if (i < 10)
		{
			numberString.prepend("0");
		}
		if (i < 100)
		{
			numberString.prepend("0");
		}
		if (i < 1000)
		{
			numberString.prepend("0");
		}
		if (i < 10000)
		{
			numberString.prepend("0");
		}
		testImage.load(":/BBBTestVideo/big_buck_bunny_" + numberString + ".png");

		QSize testSize(640, 360);
		model::frame::FrameMetadata frameMetadata(testSize);
		//frames.append(model::frame::Frame::sptr(new model::frame::Frame(testContext, testImage, frameMetadata)));
	}
}


BBBTestVideo::~BBBTestVideo()
{
}

model::video::VideoMetadata BBBTestVideo::getMetadata() const
{
	return metadata;
}

model::frame::Frame::sptr BBBTestVideo::getFrame(unsigned int frameNumber) const
{
	return frames[frameNumber];
}

unsigned int BBBTestVideo::getFrameCount() const
{
	return frames.size();
}

bool BBBTestVideo::uses(const model::Module &module) const
{
	return (this == &module);
}

model::saveable::Memento BBBTestVideo::getMemento() const
{
    throw new NotImplementedException();
}

void BBBTestVideo::restore(model::saveable::Memento memento)
{
    throw new NotImplementedException();
}

QList<model::Module*> BBBTestVideo::getUsesList() const
{
	return (QList<model::Module*>());
}

