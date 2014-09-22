#include "MacroblockOverlay.h"

#include "GPUSurfacePainter.h"
#include "GlobalContext.h"

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
using ::exception::IllegalStateException;

const QByteArray MacroblockOverlay::kFilterID = QT_TRANSLATE_NOOP("Filter", "overlay_macroblock");
const float MacroblockOverlay::kBlockAlpha = 0.5f;

MacroblockOverlay::MacroblockOverlay(Module::sptr predecessor)
    : ColoringOverlay(predecessor, Macroblocks::sptr(new Macroblocks(predecessor)), 1.f) {
}

MacroblockOverlay::~MacroblockOverlay() {
}

QList<const ::model::Module*> MacroblockOverlay::getUsesList() const {
    QList<const Module*> list = ColoringOverlay::getUsesList();

    return list;
}

Memento MacroblockOverlay::getMemento() const {
    return ColoringOverlay::getMemento();
}

void MacroblockOverlay::restore(Memento memento) {
    ColoringOverlay::restore(memento);
}

MacroblockOverlay::MacroblockOverlay() : ColoringOverlay() {
    isDummyFlag = true;
}

MacroblockOverlay::Macroblocks::Macroblocks(Module::sptr predecessor)
        : Filter(predecessor)
        , doIndexRestartPosition(false)
        , doIndexRestartColor(false)
        , doIndexRestartTexcrd(false)
        , partitionMap(new Frame(GlobalContext::get(), QImage(":/Shader/Overlay/partitions.png"))) {

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
            blockColor.setRgb(0, 0, 0, 0);
            break;
        case MacroblockType::INTER_16X16:
        case MacroblockType::INTER_16X8:
        case MacroblockType::INTER_8X16:
        case MacroblockType::INTER_8X8:
        case MacroblockType::INTER_8X4:
        case MacroblockType::INTER_4X8:
        case MacroblockType::INTER_4X4:
        case MacroblockType::INTER_8X8_OR_BELOW:
            // inter block
            blockColor.setRgb(0, 128, 0, 255 * MacroblockOverlay::kBlockAlpha);
            break;
        case MacroblockType::INTRA_4X4:
        case MacroblockType::INTRA_16X16:
        case MacroblockType::INTRA_8X8:
        case MacroblockType::INTRA_PCM:
            // intra block
            blockColor.setRgb(128, 0, 0, 255 * MacroblockOverlay::kBlockAlpha);
            break;
        case MacroblockType::UNKNOWN:
        default:
            // invalid values
            throw IllegalStateException("An unknown macroblock type was passed.");
    }

    return blockColor;
}

QRectF MacroblockOverlay::Macroblocks::getPartitionTextureCoordinates(MacroblockType type) const {
    // coordinates reference 'Shader/Overlay/partitions.png'

    switch (type) {
        // first the sub macroblock types
        case MacroblockType::INTER_4X8:
            return QRectF(2.f/3, 1.f/3, 1.f/3, 1.f/3); // middle right
        case MacroblockType::INTER_8X4:
            return QRectF(1.f/3,   0.f, 1.f/3, 1.f/3); // bottom middle
        case MacroblockType::INTER_4X4:
        case MacroblockType::INTRA_4X4:
            return QRectF(2.f/3, 0.f, 1.f/3, 1.f/3); // bottom right

        // now the macroblock types
        case MacroblockType::INTER_SKIP:
        case MacroblockType::INTER_16X16:
        case MacroblockType::INTRA_16X16:
        // we didn't find information on PCM - leave it blank
        case MacroblockType::INTRA_PCM:
            // no image
            return QRectF(  0.f, 2.f/3, 1.f/3, 1.f/3); // top left
        case MacroblockType::INTER_8X16:
            // vertical line
            return QRectF(1.f/3, 2.f/3, 1.f/3, 1.f/3); // top middle
        case MacroblockType::INTER_16X8:
            // horizontal line
            return QRectF(  0.f, 1.f/3, 1.f/3, 1.f/3); // middle left
        case MacroblockType::INTER_8X8:
        case MacroblockType::INTER_8X8_OR_BELOW:
        case MacroblockType::INTRA_8X8:
            // cross
            return QRectF(1.f/3, 1.f/3, 1.f/3, 1.f/3); // middle

        // unknown block types
        case MacroblockType::UNKNOWN:
        default:
            // invalid values
            throw IllegalStateException("An unknown macroblock type was passed.");
    }
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

    lastPosition = position;

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

    lastColor = color;

    for (unsigned int i = 0; i < count; i++) {
        *colorAttribute << color.redF()
                        << color.greenF()
                        << color.blueF()
                        << color.alphaF();
    }
}

void MacroblockOverlay::Macroblocks::appendTexcrd(QPointF texcrd) const {
    // to isolate from the last row add the last vertex of the old and the first vertex of the new row again
    if (doIndexRestartTexcrd) {
        doIndexRestartTexcrd = false;
        appendTexcrd(lastTexcrd);
        appendTexcrd(texcrd);
    }

    lastTexcrd = texcrd;

    *texcrdAttribute << texcrd.x()
                     << texcrd.y();
}

void MacroblockOverlay::Macroblocks::appendQuadCoordinates(QRectF texcrd) const {
    appendTexcrd(texcrd.topLeft());
    appendTexcrd(texcrd.bottomLeft());
    appendTexcrd(texcrd.topRight());
    appendTexcrd(texcrd.bottomRight());
}

void MacroblockOverlay::Macroblocks::indexRestart() const {
    doIndexRestartPosition = true;
    doIndexRestartColor = true;
    doIndexRestartTexcrd = true;
}

void MacroblockOverlay::Macroblocks::buildBuffers(QVector<QVector<MacroblockType>> mbTypes) const {
    // get metadata and the number of macroblocks in each direction

    QSize mbDimensions(mbTypes[0].size(), mbTypes.size());

    QSizeF relativeMbSize(2.f / mbDimensions.width(),
                          2.f / mbDimensions.height());
    
    // every quad needs 6 vertices except the first and last which need only 5
    const unsigned int vertexCnt = mbDimensions.width() * mbDimensions.height() * 6 - 2;

    positionAttribute->reset(vertexCnt, 2);
    colorAttribute->reset(vertexCnt, 4);
    texcrdAttribute->reset(vertexCnt, 2);

    startBuilder();

    // go over every macroblock and append a colored quad to the draw list
    for (int y = 0; y < mbDimensions.height(); y++) {
        QVector<MacroblockType> row = mbTypes[y];
        for (int x = 0; x < mbDimensions.width(); x++) {
            MacroblockType mbType = row[x];

            // color
            QColor color = getMacroblockColor(mbType);
            append(color, 4);

            // position (mirror y for OpengGL)
            QPointF topLeft(  x * relativeMbSize.width() - 1,
                            -(y * relativeMbSize.height() - 1) - relativeMbSize.height());
            append(QRectF(topLeft, relativeMbSize));

            // texture coordinates
            QRectF texcrdQuad = getPartitionTextureCoordinates(mbType);
            appendQuadCoordinates(texcrdQuad);

            indexRestart();
        }
    }
}

Frame::sptr MacroblockOverlay::Macroblocks::getFrame(unsigned int frameNumber) const {
    Frame::sptr sourceFrame = getPredecessor()->getFrame(frameNumber);
    FrameMetadata metadata = sourceFrame->getMetadata();

    if (!metadata.hasMbType()) {
        throw IllegalStateException("Frame does not contain any macroblock metadata to be used with the overlay.");
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
    painter.setValue("partitionMap", partitionMap);

    painter.setTargetTexture(Surface::sptr(new Surface(sourceFrame->getContext(), sourceFrame->getSize())));

    return Frame::sptr(new Frame(painter.run(), metadata));
}

Memento MacroblockOverlay::Macroblocks::getMemento() const {
    return Memento();
}

void MacroblockOverlay::Macroblocks::restore(::model::saveable::Memento memento) {
    partitionMap = Frame::sptr::create(GlobalContext::get(), QImage(":/Shader/Overlay/partitions.png"));

    positionAttribute.reset(new VertexAttribute(0, 0));
    colorAttribute.reset(new VertexAttribute(0, 0));
    texcrdAttribute.reset(new VertexAttribute(0, 0));
}

QList<const Module*> MacroblockOverlay::Macroblocks::getUsesList() const {
    return Filter::getUsesList();
}

Saveable::sptr MacroblockOverlay::getDummy() {
    return Saveable::sptr(new MacroblockOverlay());
}

}  // namespace overlay
}  // namespace filter
}  // namespace model