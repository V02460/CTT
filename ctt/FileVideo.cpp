#include "FileVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

FileVideo::FileVideo(QDir path) : path(path) {
    throw new NotImplementedException();
}

QDir FileVideo::getPath() const {
	if (isDummy()) {
		throw new IllegalStateException("Tried to request the path of a dummy FileVideo.");
	}
	return path;
}

}  // namespace video
}  // namespace model