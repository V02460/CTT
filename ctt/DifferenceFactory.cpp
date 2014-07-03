#include "DifferenceFactory.h"

namespace model {
namespace difference {

using ::model::difference::FrameDiff;
using ::model::video::Video;

QList<QString> DifferenceFactory::getAllFrameDiffIDs() {

}

QList<QString> DifferenceFactory::getAllPixelDiffIDs() {

}

FrameDiff::sptr DifferenceFactory::createFrameDiff(QString id, Video::sptr video1, Video::sptr video2) {

}

PixelDiff::sptr DifferenceFactory::createPixelDiff(QString id, Video::sptr video1, Video::sptr video2) {

}

}  // namespace difference
}  // namcespace model