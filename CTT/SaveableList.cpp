#include "SaveableList.h"

#include "FileVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "FrameDiff.h"
#include "Overlay.h"
#include "Video.h"

#include "NotImplementedException.h"
#include "IllegalStateException.h"

#include "EarthMoversHistogramDiff.h"
#include "PixelDiff.h"
#include "HSLPixelDiff.h"
#include "YUVPixelDiff.h"
#include "BlurFilter.h"
#include "CoffeeFilter.h"
#include "GreyscaleFilter.h"
#include "NoiseFilter.h"
#include "ColoringOverlay.h"
#include "HeatmapOverlay.h"
#include "MacroblockOverlay.h"
#include "MacropartitionOverlay.h"
#include "MotionVectorOverlay.h"
#include "RescaleFilter.h"
#include "RGBChannelFilter.h"
#include "TimeshiftFilter.h"
#include "FFmpegDataVideo.h"
#include "YUVDataVideo.h"
#include "FilteredVideo.h"
#include "SaveableList.h"
#include "ViewState.h"

namespace model {
namespace saveable {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

template <class T>
SaveableList<T>::SaveableList() : list() {}

template <class T> const QString SaveableList<T>::SIZE = "size";
template <class T> const QString SaveableList<T>::TEMPLATE = "template";
template <class T> const QString SaveableList<T>::ELEMENT = "element";

template <class T>
void SaveableList<T>::insert(int index, typename T::sptr element) {
	if (isDummy()) {
		throw new IllegalStateException("Called method at dummy class.");
	}
	if (index < 0 || getSize() < index) {
		throw new IllegalArgumentException("Out of saveable list bounds");
	}
	list.insert(index, element);
	changed();
}

template <class T>
typename T::sptr SaveableList<T>::remove(int index) {
	if (isDummy()) {
		throw new IllegalStateException("Called method at dummy class.");
	}
	if (index < 0 || getSize() < index) {
		throw new IllegalArgumentException("Out of saveable list bounds");
	}
	T::sptr element = get(index);
	list.removeAt(index);
	changed();
	return element;
}

template <class T>
const typename T::sptr SaveableList<T>::get(int index) const {
	if (isDummy()) {
		throw new IllegalStateException("Called method at dummy class.");
	}
	if (index < 0 || index > getSize() - 1) {
		throw new IllegalArgumentException("Out of saveable list bounds");
	}
	return list[index];
}

template <class T>
const int SaveableList<T>::getSize() const {
	if (isDummy()) {
		throw new IllegalStateException("Called method at dummy class.");
	}
	return list.size();
}

template <class T>
const ::model::saveable::Saveable::SaveableType SaveableList<T>::getTemplateType() {
	return T::getSaveableType();
}

template <class T>
Memento SaveableList<T>::getMemento() const {
	if (isDummy()) {
		throw new IllegalStateException("Called method at dummy class.");
	}
	Memento memento;
	int size = getSize();
	memento.setInt(SIZE, size);
    // TODO T::getDummy()
	memento.setString(TEMPLATE, Saveable::SAVEABLE_TYPE_STRINGS[T::getSaveableType()]);
	for (int i = 0; i < size; i++) {
		memento.setSharedPointer(ELEMENT + i, get(i));
	}
	return memento;
}

template <class T>
void SaveableList<T>::restore(Memento memento) {
    list.clear();
	int size = memento.getInt(SIZE);
	for (int i = 0; i < size; i++) {
		// TODO works?
		list.append(memento.getSharedPointer(ELEMENT + i).dynamicCast<T>());
	}
	isDummyFlag = false;
}

template <class T>
Saveable::sptr SaveableList<T>::getDummy() {
	SaveableList<T>::sptr dummyPointer(new SaveableList<T>());
	dummyPointer->isDummyFlag = true;
	return dummyPointer;
}

template <class T>
Saveable::SaveableType SaveableList<T>::getSaveableType() {
    return SaveableType::saveableList;
}

// A list of all objects which might be used with the SaveableList
// This is necessary because *.cpp files are compiled separate, so it's unknown for the compiler for which types to
// generate code.
template class SaveableList<model::saveable::Saveable>;
template class SaveableList<model::FilterIntervalList>;
template class SaveableList<model::difference::FrameDiff>;
template class SaveableList<model::difference::EarthMoversHistogramDiff>;
template class SaveableList<model::difference::PixelDiff>;
template class SaveableList<model::difference::HSLPixelDiff>;
template class SaveableList<model::difference::YUVPixelDiff>;
template class SaveableList<model::Module>;
template class SaveableList<model::filter::Filter>;
template class SaveableList<model::filter::BlurFilter>;
template class SaveableList<model::filter::CoffeeFilter>;
template class SaveableList<model::filter::GreyscaleFilter>;
template class SaveableList<model::filter::MixFilter>;
template class SaveableList<model::filter::NoiseFilter>;
template class SaveableList<model::filter::overlay::Overlay>;
template class SaveableList<model::filter::overlay::ColoringOverlay>;
template class SaveableList<model::filter::overlay::HeatmapOverlay>;
template class SaveableList<model::filter::overlay::MacroblockOverlay>;
template class SaveableList<model::filter::overlay::MacropartionOverlay>;
template class SaveableList<model::filter::overlay::MotionVectorOverlay>;
template class SaveableList<model::filter::RescaleFilter>;
template class SaveableList<model::filter::RGBChannelFilter>;
template class SaveableList<model::filter::TimeshiftFilter>;
template class SaveableList<model::video::Video>;
template class SaveableList<model::video::FileVideo>;
template class SaveableList<model::video::FFmpegDataVideo>;
template class SaveableList<model::video::YUVDataVideo>;
template class SaveableList<model::filter::FilteredVideo>;
template class SaveableList<model::player::Player>;
template class SaveableList<model::UIntegerInterval>;
template class SaveableList<model::player::VideoScrubber>;
template class SaveableList<view::ViewState>;

}  // namespace saveable
}  // namespace model