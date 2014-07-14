#include "DifferenceFactory.h"

#include "NotImplementedException.h"

namespace model {
namespace difference {

using ::model::difference::FrameDiff;
using ::model::video::Video;
using ::exception::NotImplementedException;

QList<QString> DifferenceFactory::getAllFrameDiffIDs() {
    throw new NotImplementedException();
}

QList<QString> DifferenceFactory::getAllPixelDiffIDs() {
    throw new NotImplementedException();
}

FrameDiff::sptr DifferenceFactory::createFrameDiff(QString id, Video::sptr video1, Video::sptr video2) {
    throw new NotImplementedException();
}

PixelDiff::sptr DifferenceFactory::createPixelDiff(QString id, Video::sptr video1, Video::sptr video2) {
    throw new NotImplementedException();
}

}  // namespace difference
}  // namespace model