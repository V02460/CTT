#pragma once

#include "Video.h"
#include "VideoMetadata.h"
#include "Frame.h"
#include <QOffscreenSurface>

class BBBTestVideo :
	public model::video::Video
{
public:
	//frames not higher than 50
	BBBTestVideo(unsigned int frames);

	model::video::VideoMetadata getMetadata() const;

	model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;

	unsigned int getFrameCount() const;

	bool uses(const model::Module &module) const;

	model::saveable::Memento getMemento() const;

	void restore(model::saveable::Memento memento);

	QList<const Module*> getUsesList() const;

	~BBBTestVideo();

private:
	model::video::VideoMetadata metadata;
	QList<model::frame::Frame::sptr> frames;
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;

	BBBTestVideo();
};

