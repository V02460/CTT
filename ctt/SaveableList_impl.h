#ifndef _SAVEABLELIST_IMPL_H
#define _SAVEABLELIST_IMPL_H

#include "AccessToDummyException.h"

namespace model {
namespace saveable {

using ::exception::AccessToDummyException;

template <class T> const QString SaveableList<T>::SIZE = "size";
template <class T> const QString SaveableList<T>::TEMPLATE = "template";
template <class T> const QString SaveableList<T>::ELEMENT = "element";

template <class T>
SaveableList<T>::SaveableList() {}

template <class T>
void SaveableList<T>::insert(int index, typename T::sptr element) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (index < 0 || getSize() < index) {
		throw IllegalArgumentException("Out of saveable list bounds");
	}
	list.insert(index, element);
	changed();
}

template <class T>
typename T::sptr SaveableList<T>::remove(int index) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (index < 0 || getSize() < index) {
		throw IllegalArgumentException("Out of saveable list bounds");
	}
	T::sptr element = get(index);
	list.removeAt(index);
	changed();
	return element;
}

template <class T>
Saveable::SaveableType SaveableList<T>::saveableType() const {
	return getSaveableType();
}

template <class T>
const typename T::sptr SaveableList<T>::get(int index) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (index < 0 || index > getSize() - 1) {
		throw IllegalArgumentException("Out of saveable list bounds");
	}
	return list[index];
}

template <class T>
const int SaveableList<T>::getSize() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return list.size();
}

template <class T>
const ::model::saveable::Saveable::SaveableType SaveableList<T>::getTemplateType() {
	return T::getSaveableType();
}

template <class T>
void SaveableList<T>::clear() {
	list.clear();
	changed();
}

template <class T>
Memento SaveableList<T>::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;
	int size = getSize();
	memento.setInt(SIZE, size);
	memento.setString(TEMPLATE, Saveable::SAVEABLE_TYPE_STRINGS[T::getSaveableType()]);
	for (int i = 0; i < size; i++) {
		memento.setSharedPointer(ELEMENT + QString::number(i), get(i));
	}
	return memento;
}

template <class T>
void SaveableList<T>::restore(Memento memento) {
    list.clear();
	int size = memento.getInt(SIZE);
	for (int i = 0; i < size; i++) {
		list.append(memento.getSharedPointer(ELEMENT + QString::number(i)).dynamicCast<T>());
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

}  // namespace saveable
}  // namespace model

#endif  //_SAVEABLELIST_IMPL_H