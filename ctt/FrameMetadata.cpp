#include "FrameMetadata.h"

namespace model {
namespace frame {

using exception::IllegalStateException;

FrameMetadata::FrameMetadata(QSize size)
        : size(size)
        , hasMbTypeFlag(false)
        , hasMbMotionvectorsFlag(false) {
}

FrameMetadata::FrameMetadata(QSize size,
                             QVector<QVector<MacroblockType>> macroblockTypes,
                             QVector<QVector<QVector2D>> macroblockMotionvectors)
        : size(size)
        , hasMbTypeFlag(true)
        , hasMbMotionvectorsFlag(true)
        , mbTypes(macroblockTypes) 
        , mbMotionvectors(macroblockMotionvectors) {
}

FrameMetadata::FrameMetadata(QSize size, QVector<QVector<MacroblockType>> macroblockTypes)
		: size(size)
		, hasMbTypeFlag(true)
		, hasMbMotionvectorsFlag(false)
		, mbTypes(macroblockTypes) {

}

QSize FrameMetadata::getSize() const {
    return size;
}

QVector<QVector<MacroblockType>> FrameMetadata::getMbType() const {
    if (!hasMbType()) {
        throw new IllegalStateException("FrameMetadata object has no macroblock type information.");
    }

    return mbTypes;
}


QVector<QVector<QVector2D>> FrameMetadata::getMbMotionvectors() const {
    if (!hasMbMotionvectors()) {
        throw new IllegalStateException("FrameMetadata object has no motion vector information.");
    }

    return mbMotionvectors;
}

bool FrameMetadata::hasMbType() const {
    return hasMbTypeFlag;
}

bool FrameMetadata::hasMbMotionvectors() const {
    return hasMbMotionvectorsFlag;
}

}  // namespace frame
}  // namespace model