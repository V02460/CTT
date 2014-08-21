#include "FilterFactory.h"

#include "BlurFilter.h"
#include "CoffeeFilter.h"
#include "GreyscaleFilter.h"
#include "MixFilter.h"
#include "NoiseFilter.h"
#include "RescaleFilter.h"
#include "RGBChannelFilter.h"
#include "TimeshiftFilter.h"

#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"
#include "MotionVectorOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using overlay::HeatmapOverlay;
using overlay::MacroblockOverlay;
using overlay::MotionVectorOverlay;
using exception::NotImplementedException;

QList<QString> FilterFactory::getAllNonOverlayFilterIDs() {
    QList<QString> list;

    return list 
        << "filter_blur"
        << "filter_coffee"
        << "filter_greyscale"
        //<< "filter_mix"
        << "filter_noise"
        << "filter_rescale"
        << "filter_rgbchannel"
        << "filter_timeshift";
}

QList<QString> FilterFactory::getAllOverlayIDs() {
    QList<QString> list;

    return list
        << "overlay_heatmap"
        << "overlay_macroblock"
        << "overlay_motionvector";
}

Filter::sptr FilterFactory::createFilter(QString id, Module::sptr predecessor) {
    if (id == "filter_blur") { return BlurFilter::sptr(new BlurFilter(predecessor)); }
    if (id == "filter_coffee") { return CoffeeFilter::sptr(new CoffeeFilter(predecessor)); }
    if (id == "filter_greyscale") { return GreyscaleFilter::sptr(new GreyscaleFilter(predecessor)); }
    //if (id == "filter_mix") { return MixFilter::sptr(new MixFilter(predecessor)); }
    if (id == "filter_noise") { return NoiseFilter::sptr(new NoiseFilter(predecessor)); }
    if (id == "filter_rescale") { return RescaleFilter::sptr(new RescaleFilter(predecessor)); }
    if (id == "filter_rgbchannel") { return RGBChannelFilter::sptr(new RGBChannelFilter(predecessor)); }
    if (id == "filter_timeshift") { return TimeshiftFilter::sptr(new TimeshiftFilter(predecessor)); }

    if (id == "overlay_heatmap") {
        // return HeatmapOverlay::sptr(new HeatmapOverlay(predecessor));
        throw new NotImplementedException();
    }
    if (id == "overlay_macroblock") { return MacroblockOverlay::sptr(new MacroblockOverlay(predecessor)); }
    if (id == "overlay_motionvector") { return MotionVectorOverlay::sptr(new MotionVectorOverlay(predecessor)); }

    throw new IllegalArgumentException("There is no filter with this id to create.");
}

}  // namespace filter
}  // namespace model