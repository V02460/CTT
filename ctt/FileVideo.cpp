#include "FileVideo.h"

#include "NotImplementedException.h"
#include "FileNotFoundException.h"

namespace model {
namespace video {

using ::model::Module;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::exception::FileNotFoundException;


FileVideo::FileVideo(QString path, QSharedPointer<QOpenGLContext> context) 
		: pathToVideoFile(path)
		, context(context)
		, videoFile(path)
{
	if (!videoFile.exists())
	{
		throw new FileNotFoundException("The video file at \"" + path + "\" doesn't exist");
	}
}
using ::model::saveable::Saveable;

FileVideo::FileVideo()
{

}

QString FileVideo::getPath() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the path of a dummy FileVideo.");
	}
	return pathToVideoFile;
}

QList<const Module*> FileVideo::getUsesList() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request a list of used modules from a dummy FileVideo.");
	}

	QList<const Module*> uses;
	uses.append(this);

	return uses;
}

bool FileVideo::uses(const Module &module) const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to ask a dummy FileVideo whether it used a specific module.");
	}

	return (this == &module);
}

QSharedPointer<QOpenGLContext> FileVideo::getContext() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the context from a dummy FileVideo.");
	}

	return context;
}

Saveable::SaveableType FileVideo::getSaveableType() {
	return Saveable::fileVideo;
}

}  // namespace video
}  // namespace model