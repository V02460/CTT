#include "SaveableList.h"

#include "FileVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "FrameDiff.h"
#include "Overlay.h"
#include "Video.h"

namespace model {
namespace saveable {

template <class T>
SaveableList<T>::SaveableList() {

}

template <class T>
void SaveableList<T>::insert(unsigned int index, typename T::sptr element) {

}

template <class T>
typename T::sptr SaveableList<T>::remove(unsigned int index) {

}

template <class T>
const T &SaveableList<T>::get(unsigned int index) const {

}

template <class T>
const unsigned int SaveableList<T>::getSize() const {

}

template <class T>
Memento SaveableList<T>::getMemento() const {

}

template <class T>
void SaveableList<T>::restore(Memento memento) {

}

template <class T>
Saveable::sptr SaveableList<T>::getDummy() {

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