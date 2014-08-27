#include "SaveableListTest.h"

#include "../CTT/UIntegerInterval.h"
#include "../CTT/Memento.h"

#include "../CTT/IllegalStateException.h"

using ::model::saveable::SaveableList;
using ::model::saveable::Saveable;
using ::model::UIntegerInterval;
using ::exception::IllegalStateException;
using ::model::saveable::Memento;

void SaveableListTest::setAndGet() {
	SaveableList<Saveable> list;
	Saveable::sptr element0 = QSharedPointer<Saveable>(new UIntegerInterval(0, 10));
	Saveable::sptr element1 = QSharedPointer<Saveable>(new UIntegerInterval(1, 11));
	Saveable::sptr element2 = QSharedPointer<Saveable>(new UIntegerInterval(2, 12));
	Saveable::sptr element3 = QSharedPointer<Saveable>(new UIntegerInterval(3, 13));
	list.insert(0, element1);
	list.insert(1, element2);
	list.insert(0, element0);
    list.insert(list.getSize(), element3);
    QCOMPARE(list.getSize(), 4);
	QCOMPARE(list.get(0), element0);
	QCOMPARE(list.get(1), element1);
	QCOMPARE(list.get(2), element2);
	QCOMPARE(list.get(3), element3);
}

void SaveableListTest::remove() {
	//TODO: fix memory leak
	//TIPP: SaveableList<Saveable> list; w�rde reichen
	SaveableList<Saveable> list;
	Saveable::sptr element0 = QSharedPointer<Saveable>(new UIntegerInterval(0, 10));
	Saveable::sptr element1 = QSharedPointer<Saveable>(new UIntegerInterval(1, 11));
	list.insert(0, element0);
	list.insert(0, element1);
	QCOMPARE(list.getSize(), 2);
	QCOMPARE(list.remove(0), element1);
	QCOMPARE(list.get(0), element0);
	QCOMPARE(list.getSize(), 1);
}

void SaveableListTest::outOfBounds() {
	SaveableList<Saveable> list;
	Saveable::sptr element = QSharedPointer<Saveable>(new UIntegerInterval(0, 1));
	QEXPECT_EXCEPTION(list.insert(-1, element), IllegalArgumentException);
	QEXPECT_EXCEPTION(list.insert(5, element), IllegalArgumentException);
	QEXPECT_EXCEPTION(list.get(0), IllegalArgumentException);
}

// TODO: WTF WTF WTF !!!
void SaveableListTest::dummyCheck() {
	SaveableList<Saveable>::sptr list = SaveableList<Saveable>::getDummy().dynamicCast<SaveableList<Saveable>>();
	Saveable::sptr element = QSharedPointer<Saveable>(new UIntegerInterval(0, 1));
	QEXPECT_EXCEPTION(list->insert(0, element), IllegalStateException);
	QEXPECT_EXCEPTION(list->remove(0), IllegalStateException);
	QEXPECT_EXCEPTION(list->get(0), IllegalStateException);
	QEXPECT_EXCEPTION(list->getSize(), IllegalStateException);
	QEXPECT_EXCEPTION(list->getMemento(), IllegalStateException);
}

void SaveableListTest::mementoAndRestore() {
	SaveableList<Saveable> originalList;
	Saveable::sptr element0(new UIntegerInterval(0, 10));
	Saveable::sptr element1(new UIntegerInterval(1, 11));
	Saveable::sptr element2(new UIntegerInterval(2, 12));
	Saveable::sptr element3(new UIntegerInterval(3, 13));
	originalList.insert(0, element0);
	originalList.insert(0, element1);
	originalList.insert(0, element2);
	originalList.insert(0, element3);
	Memento memento = originalList.getMemento();
    SaveableList<Saveable> restoredList;
	restoredList.insert(0, element3);
	restoredList.restore(memento);
	QCOMPARE(originalList.getSize(), restoredList.getSize());
	for (int i = 0; i < originalList.getSize(); i++) {
		QCOMPARE(originalList.get(i), restoredList.get(i));
	}
}