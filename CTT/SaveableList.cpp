#include "SaveableList.h"

#include "FileVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "FrameDiff.h"
#include "Overlay.h"
#include "Video.h"

#include "NotImplementedException.h"

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
		// TODO casting list.append(memento.getSharedPointer("element" + i));
		throw new NotImplementedException();
	}
	isDummyFlag = false;
}

template <class T>
Saveable::sptr SaveableList<T>::getDummy() {
	SaveableList<T> dummy = SaveableList<T>();
	dummy.isDummyFlag = true;
	// TODO return SaveableList<T>>(dummy);
	throw new NotImplementedException();
}

// A list of all objects which might be used with the SaveableList
// This is necessary because *.cpp files are compiled separate, so it's unknown for the compiler for which types to
// generate code.
template class SaveableList<::model::video::FileVideo>;
template class SaveableList<::model::filter::FilteredVideo>;
template class SaveableList<::model::player::Player>;
template class SaveableList<::model::difference::FrameDiff>;
template class SaveableList<::model::filter::overlay::Overlay>;
template class SaveableList<::model::video::Video>;

}  // namespace saveable
}  // namespace model