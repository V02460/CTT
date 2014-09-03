#include "FilterFactory.h"

#include "BlurFilter.h"
#include "CoffeeFilter.h"
#include "GreyscaleFilter.h"
#include "MixFilter.h"
#include "NoiseFilter.h"
#include "RescaleFilter.h"
#include "RGBChannelFilter.h"
#include "TimeshiftFilter.h"
#include "InvertFilter.h"

#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"
#include "MotionVectorOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using overlay::HeatmapOverlay;
using overlay::MacroblockOverlay;
using overlay::MotionVectorOverlay;
using ::model::difference::PixelDiff;
using exception::NotImplementedException;

QList<QByteArray> FilterFactory::getAllNonOverlayFilterIDs() {
    QList<QByteArray> list;

    return list 
        << BlurFilter::kFilterID
        //<< CoffeFilter::kFilterID
        << GreyscaleFilter::kFilterID
        //<< MixFilter::kFilterID
        << NoiseFilter::kFilterID
        //<< RescaleFilter::kFilterID
        << RGBChannelFilter::kFilterID
        << TimeshiftFilter::kFilterID
        << InvertFilter::kFilterID;
}

QList<QByteArray> FilterFactory::getAllOverlayIDs() {
    QList<QByteArray> list;

    return list
        //<< HeatmapOverlay::kFilterID
        << MacroblockOverlay::kFilterID
        /*<< MotionVectorOverlay::kFilterID*/;
}

Filter::sptr FilterFactory::createFilter(QString id, Module::sptr predecessor) {
    if (id == BlurFilter::kFilterID) { return BlurFilter::sptr(new BlurFilter(predecessor)); }
    //if (id == CoffeFilter::kFilterID) { return CoffeeFilter::sptr(new CoffeeFilter(predecessor)); }
    if (id == GreyscaleFilter::kFilterID) { return GreyscaleFilter::sptr(new GreyscaleFilter(predecessor)); }
    //if (id == MixFilter::kFilterID) { return MixFilter::sptr(new MixFilter(predecessor)); }
    if (id == NoiseFilter::kFilterID) { return NoiseFilter::sptr(new NoiseFilter(predecessor)); }
    if (id == RescaleFilter::kFilterID) { return RescaleFilter::sptr(new RescaleFilter(predecessor)); }
    if (id == RGBChannelFilter::kFilterID) { return RGBChannelFilter::sptr(new RGBChannelFilter(predecessor)); }
    if (id == TimeshiftFilter::kFilterID) { return TimeshiftFilter::sptr(new TimeshiftFilter(predecessor)); }
    if (id == InvertFilter::kFilterID) { return InvertFilter::sptr(new InvertFilter(predecessor)); }

    if (id == HeatmapOverlay::kFilterID) {
        throw IllegalArgumentException("HeatmapOverlay needs a PixelDiff to get created.");
    }
    if (id == MacroblockOverlay::kFilterID) { return MacroblockOverlay::sptr(new MacroblockOverlay(predecessor)); }
    if (id == MotionVectorOverlay::kFilterID) { return MotionVectorOverlay::sptr(new MotionVectorOverlay(predecessor)); }

    throw IllegalArgumentException("There is no filter with this id to create.");
}

Filter::sptr FilterFactory::createFilter(QString id, Module::sptr predecessor, PixelDiff::sptr pixelDiff) {
    if (id == HeatmapOverlay::kFilterID) {
        return HeatmapOverlay::sptr(new HeatmapOverlay(predecessor, pixelDiff));
    }

    return createFilter(id, predecessor);
}

}  // namespace filter
}  // namespace model