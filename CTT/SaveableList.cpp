#include "SaveableList.h"

#include "FileVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "FrameDiff.h"
#include "Overlay.h"
#include "Video.h"

#include "NotImplementedException.h"

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

template <class T>
SaveableList<T>::SaveableList() {}

template <class T>
void SaveableList<T>::insert(unsigned int index, typename T::sptr element) {
	list.insert(index, element);
}

template <class T>
typename T::sptr SaveableList<T>::remove(unsigned int index) {
	T::sptr element = get(index);
	list.removeAt(index);
	return element;
}

template <class T>
const typename T::sptr SaveableList<T>::get(unsigned int index) const {
	return list[index];
}

template <class T>
const unsigned int SaveableList<T>::getSize() const {
	return list.size();
}

template <class T>
const ::model::saveable::Saveable::SaveableType SaveableList<T>::getTemplateType() {
	return T::getDummy()->getType();
}


template <class T>
Memento SaveableList<T>::getMemento() const {
	Memento memento = Memento();
	int size = getSize();
	memento.setInt("size", size);
	for (int i = 0; i < size; i++) {
		memento.setSharedPointer("element" + i, get(i));
	}
	return memento;
}

template <class T>
void SaveableList<T>::restore(Memento memento) {
	int size = memento.getInt("size");
	for (int i = 0; i < size; i++) {
		// TODO how to cast to T? every method seperate :/
		// list.append(memento.getSharedPointer("element" + QString::number(i)));
		throw new NotImplementedException();
	}
	isDummyFlag = false;
}

template <class T>
Saveable::sptr SaveableList<T>::getDummy() {
	SaveableList<T> *dummy = new SaveableList<T>();
	dummy->isDummyFlag = true;
	SaveableList<T>::sptr dummyPointer = QSharedPointer<SaveableList<T>>(dummy);
	return dummyPointer;
}

template <class T>
Saveable::SaveableType SaveableList<T>::getType() const {
	return Saveable::SaveableType::saveableList;
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