#include "DifferenceFactory.h"
#include "FrameDiff.h"
#include "Video.h"

namespace model {
namespace difference {

QList<QString> DifferenceFactory::getAllDiffIDs() {

}

FrameDiff::sptr DifferenceFactory::createDiff(QString id, const video::Video &video1, const video::Video &video2) {

}

}  // namespace difference
}  // namcespace model