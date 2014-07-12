#include "BBBTestVideo.h"
#include "..\ctt\Module.h"



BBBTestVideo::BBBTestVideo(unsigned int frameCount) : metadata(QSize(640, 360), 24, frameCount)
{
	surface.create();
	testContext = QSharedPointer<QOpenGLContext>(new QOpenGLContext());
	testContext->create();

	QImage testImage;

	for (int i = 1; i <= frameCount; i++)
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

}

void BBBTestVideo::restore(model::saveable::Memento memento)
{

}

QList<model::Module*> BBBTestVideo::getUsesList() const
{
	return (QList<model::Module*>());
}

