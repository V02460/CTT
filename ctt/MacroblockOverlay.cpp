#include "MacroblockOverlay.h"

#include "GPUSurfacePainter.h"

#include "NotImplementedException.h"
#include "IllegalStateException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::model::frame::FrameMetadata;
using ::model::frame::MacroblockType;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::helper::GPUSurfacePainter;
using ::helper::VertexAttribute;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

const QByteArray MacroblockOverlay::kFilterID = QT_TR_NOOP("overlay_macroblock");

MacroblockOverlay::MacroblockOverlay(Module::sptr predecessor)
    : ColoringOverlay(predecessor, Macroblocks::sptr(new Macroblocks(predecessor)), 0.5) {
}

MacroblockOverlay::~MacroblockOverlay() {
}

QList<const ::model::Module*> MacroblockOverlay::getUsesList() const {
    QList<const Module*> list;

    return list << this;
}

Memento MacroblockOverlay::getMemento() const {
    throw new NotImplementedException();
}

void MacroblockOverlay::restore(Memento memento) {
    throw new NotImplementedException();
}

bool MacroblockOverlay::uses(const ::model::Module &module) const {
    throw new NotImplementedException();
}

MacroblockOverlay::Macroblocks::Macroblocks(Module::sptr predecessor)
    : Filter(predecessor)
    , doIndexRestartPosition(false)
    , doIndexRestartColor(false) {

    positionAttribute.reset(new VertexAttribute(0, 0));
    colorAttribute.reset(new VertexAttribute(0, 0));
    texcrdAttribute.reset(new VertexAttribute(0, 0));
}

MacroblockOverlay::Macroblocks::~Macroblocks() {
}

QColor MacroblockOverlay::Macroblocks::getMacroblockColor(MacroblockType type) const {
    QColor blockColor;

    switch (type) {
        case MacroblockType::INTER_SKIP:
        case MacroblockType::INTER_16X16:
        case MacroblockType::INTER_16X8:
        case MacroblockType::INTER_8X16:
        case MacroblockType::INTER_8X8:
        case MacroblockType::INTER_8X4:
        case MacroblockType::INTER_4X8:
        case MacroblockType::INTER_4X4:
        case MacroblockType::INTER_8X8_OR_BELOW:
            // inter block
            blockColor.setRgb(128, 0, 0);
            break;
        case MacroblockType::INTRA_4X4:
        case MacroblockType::INTRA_16X16:
        case MacroblockType::INTRA_8X8:
        case MacroblockType::INTRA_PCM:
            // intra block
            blockColor.setRgb(0, 128, 0);
            break;
        case MacroblockType::UNKNOWN:
        default:
            // invalid values
            throw new IllegalStateException("An unknown macroblock type was passed.");
    }

    return blockColor;
}

void MacroblockOverlay::Macroblocks::startBuilder() const {
    doIndexRestartPosition = false;
    doIndexRestartColor = false;
    doIndexRestartTexcrd = false;
}

void MacroblockOverlay::Macroblocks::append(QRectF quad) const {
    append(quad.topLeft());
    append(quad.bottomLeft());
    append(quad.topRight());
    append(quad.bottomRight());
}

void MacroblockOverlay::Macroblocks::append(QPointF position) const {
    // to isolate from the last row add the last vertex of the old and the first vertex of the new row again
    if (doIndexRestartPosition) {
        doIndexRestartPosition = false;
        append(lastPosition);
        append(position);
    }

    *positionAttribute << position.x()
                       << position.y();
}

void MacroblockOverlay::Macroblocks::append(QColor color, unsigned int count) const {
    // to isolate from the last row add the last vertex of the old and the first vertex of the new row again
    if (doIndexRestartColor) {
        doIndexRestartColor = false;
        append(lastColor);
        append(color);
    }

    for (unsigned int i = 0; i < count; i++) {
        *colorAttribute << color.redF()
                        << color.greenF()
                        << color.blueF();
    }
}

void MacroblockOverlay::Macroblocks::indexRestart() const {
    doIndexRestartPosition = true;
    doIndexRestartColor = true;
}

void MacroblockOverlay::Macroblocks::buildBuffers(QVector<QVector<MacroblockType>> mbTypes) const {
    // get metadata and the number of macroblocks in each direction

    QSize mbDimensions(mbTypes[0].size(), mbTypes.size());

    QSizeF relativeMbSize(1.f / mbDimensions.width(),
                          1.f / mbDimensions.height());
    
    // every quad needs 6 vertices except the first and last which need only 5
    const unsigned int vertexCnt = mbDimensions.width() * mbDimensions.height() * 6 - 2;

    positionAttribute->reset(vertexCnt, 2);
    colorAttribute->reset(vertexCnt, 3);
    texcrdAttribute->reset(vertexCnt, 2);

    startBuilder();

    // go over every macroblock and append a colored quad to the draw list
    for (int y = 0; y < mbDimensions.height(); y++) {
        QVector<MacroblockType> row = mbTypes[y];
        for (int x = 0; x < mbDimensions.width(); x++) {
            MacroblockType mbType = row[x];

            QColor color = getMacroblockColor(mbType);
            append(color, 4);

            QPointF topLeft(x * relativeMbSize.width(),
                            y * relativeMbSize.height());
            append(QRectF(topLeft, relativeMbSize));

            indexRestart();
        }
    }
}

Frame::sptr MacroblockOverlay::Macroblocks::getFrame(unsigned int frameNumber) const {
    Frame::sptr sourceFrame = getPredecessor()->getFrame(frameNumber);
    FrameMetadata metadata = sourceFrame->getMetadata();

    if (!metadata.hasMbType()) {
        throw new IllegalStateException("Frame does not contain any macroblock metadata to be used with the overlay.");
    }

    QVector<QVector<MacroblockType>> mbTypes = metadata.getMbType();
    QSize mbDimensions(mbTypes[0].size(), mbTypes.size());

    buildBuffers(mbTypes);

    GPUSurfacePainter painter(":/Shader/Overlay/Macroblock.vs",
                              ":/Shader/Overlay/Macroblock.fs",
                              sourceFrame->getContext());

    painter.setValue("aPosition", positionAttribute);
    painter.setValue("aColor", colorAttribute);
    painter.setValue("aTexcrd", texcrdAttribute);

    return Frame::sptr(new Frame(painter.run(), metadata));
}

Memento MacroblockOverlay::Macroblocks::getMemento() const {
    throw new NotImplementedException(); // TODO: think about the buffers
}

void MacroblockOverlay::Macroblocks::restore(::model::saveable::Memento memento) {
    throw new NotImplementedException();
}

QList<const Module*> MacroblockOverlay::Macroblocks::getUsesList() const {
    throw new IllegalArgumentException();
}

Saveable::sptr MacroblockOverlay::getDummy() {
	throw new IllegalArgumentException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model