#include "FileVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;


FileVideo::FileVideo(QString path, QSharedPointer<QOpenGLContext> context) 
		: pathToVideoFile(path)
		, context(context)
		, videoFile(path)
{
	if (!videoFile.exists())
	{
		//TODO use the File not found exception jeshgni
		//throw new FileNotFoundException();
	}
}

FileVideo::FileVideo()
{

}

QDir FileVideo::getPath() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the path of a dummy FileVideo.");
	}
	return pathToVideoFile;
}

saveable::Saveable::sptr FileVideo::getDummy() {
	throw new NotImplementedException();
}

}  // namespace video
}  // namespace model