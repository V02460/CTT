#include "FrameMetadata.h"

namespace model {
namespace frame {

FrameMetadata::FrameMetadata(QSize size) {

}

FrameMetadata::FrameMetadata(QSize size,
                             QVector<QVector<MacroblockType>> macroblockTypes,
                             QVector<QVector<MacroblockPartition>> macroblockPartitions,
                             QVector<QVector<QVector2D>> macroblockMotionvectors) {

}

QSize FrameMetadata::getSize() const {

}

QVector<QVector<MacroblockType>> FrameMetadata::getMbType() const {

}

QVector<QVector<MacroblockPartition>> FrameMetadata::getMbPartitions() const {

}

QVector<QVector<QVector2D>> FrameMetadata::getMbMotionvectors() const {

}

bool FrameMetadata::hasMbType() const {

}

bool FrameMetadata::hasMbPartions() const {

}

bool FrameMetadata::hasMbMotionvectors() const {

}

}  // namespace frame
}  // namespace model