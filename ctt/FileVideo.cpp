#include "FileVideo.h"

#include "FileNotFoundException.h"

namespace model {
namespace video {

using ::model::Module;
using ::model::saveable::Saveable;
using ::exception::AccessToDummyException;
using ::exception::FileNotFoundException;


FileVideo::FileVideo(QString path, QSharedPointer<QOpenGLContext> context) 
		: pathToVideoFile(path)
		, context(context)
		, videoFile(path)
{
	if (!videoFile.exists())
	{
		throw FileNotFoundException("The video file at \"" + path + "\" doesn't exist");
	}
}

FileVideo::FileVideo() {}

QString FileVideo::getPath() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return pathToVideoFile;
}

QList<const Module*> FileVideo::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	QList<const Module*> uses;
	uses.append(this);

	return uses;
}

bool FileVideo::uses(const Module &module) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return (this == &module);
}

QSharedPointer<QOpenGLContext> FileVideo::getContext() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return context;
}

Saveable::SaveableType FileVideo::getSaveableType() {
	return Saveable::fileVideo;
}

}  // namespace video
}  // namespace model