#pragma once
#include "C:\Users\Jonas\Source\Repos\CTT\ctt\Video.h"
#include "..\ctt\VideoMetadata.h"
#include "..\ctt\Frame.h"
#include "QOffscreenSurface"
class BBBTestVideo :
	public model::video::Video
{
public:
	//frames not higher than 100
	BBBTestVideo(unsigned int frames, QOpenGLContext context);

	model::video::VideoMetadata getMetadata() const;

	model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

	unsigned int getFrameCount() const;

	bool uses(const model::Module &module) const;

	~BBBTestVideo();

private:
	model::video::VideoMetadata metadata;
	QList<model::frame::Frame::sptr> frames;
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;

	BBBTestVideo();
};

