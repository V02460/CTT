#include "FileVideo.h"

#include "NotImplementedException.h"
#include "FileNotFoundException.h"

namespace model {
namespace video {

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

QDir FileVideo::getPath() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the path of a dummy FileVideo.");
	}
	return pathToVideoFile;
}

QList<const Module*> FileVideo::getUsesList() const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to request a list of used modules from a dummy YUVDataVideo.");
	}

	QList<const Module*> uses;
	uses.append(this);

	return uses;
}

bool FileVideo::uses(const model::Module &module) const
{
	if (isDummy()) {
		throw new IllegalStateException("Tried to ask a dummy YUVDataVideo whether it used a specific module.");
	}

	return (this == &module);
}

}  // namespace video
}  // namespace model