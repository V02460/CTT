#include "FileVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace video {

using ::exception::NotImplementedException;

FileVideo::FileVideo(QDir path) : path(path) {
    throw new NotImplementedException();
}

QDir FileVideo::getPath() const {
    throw new NotImplementedException();
}

}  // namespace video
}  // namespace model