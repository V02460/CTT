#include <CppUnitTest.h>
#include <functional>

#include "../ctt/SaveableList.h"

#include "UIntegerInterval.h"
#include "Memento.h"

#include "IllegalStateException.h"
#include "AccessToDummyException.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

	using ::model::saveable::SaveableList;
	using ::model::saveable::Saveable;
	using ::model::UIntegerInterval;
	using ::model::saveable::Memento;
	using ::exception::IllegalStateException;
	using ::exception::AccessToDummyException;

	TEST_CLASS(SaveableListTest) {
public:
	TEST_METHOD(setAndGet) {
		SaveableList<Saveable> list;
		Saveable::sptr element0 = QSharedPointer<Saveable>(new UIntegerInterval(0, 10));
		Saveable::sptr element1 = QSharedPointer<Saveable>(new UIntegerInterval(1, 11));
		Saveable::sptr element2 = QSharedPointer<Saveable>(new UIntegerInterval(2, 12));
		Saveable::sptr element3 = QSharedPointer<Saveable>(new UIntegerInterval(3, 13));
		list.insert(0, element1);
		list.insert(1, element2);
		list.insert(0, element0);
		list.insert(list.getSize(), element3);
		list.getSize();
		list.get(0);
		list.get(1);
		list.get(2);
		list.get(3);
	}

	TEST_METHOD(remove) {
		//TODO: fix memory leak
		//TIPP: SaveableList<Saveable> list; würde reichen
		SaveableList<Saveable> list;
		Saveable::sptr element0 = QSharedPointer<Saveable>(new UIntegerInterval(0, 10));
		Saveable::sptr element1 = QSharedPointer<Saveable>(new UIntegerInterval(1, 11));
		list.insert(0, element0);
		list.insert(0, element1);
		list.getSize();
		list.remove(0);
		list.get(0);
		list.getSize();
	}


	TEST_METHOD(outOfBounds) {
		SaveableList<Saveable> list;
		Saveable::sptr element = QSharedPointer<Saveable>(new UIntegerInterval(0, 1));
		Assert::ExpectException<IllegalArgumentException>([&] {list.insert(-1, element); });
		Assert::ExpectException<IllegalArgumentException>([&] {list.insert(5, element); });
		Assert::ExpectException<IllegalArgumentException>([&] {list.get(0); });
	}

	TEST_METHOD(dummyCheck) {
		SaveableList<Saveable>::sptr list = SaveableList<Saveable>::getDummy().dynamicCast<SaveableList<Saveable>>();
		Saveable::sptr element = QSharedPointer<Saveable>(new UIntegerInterval(0, 1));
		Assert::ExpectException<AccessToDummyException>([&] {list->insert(0, element); });
		Assert::ExpectException<AccessToDummyException>([&] {list->remove(0); });
		Assert::ExpectException<AccessToDummyException>([&] {list->get(0); });
		Assert::ExpectException<AccessToDummyException>([&] {list->getSize(); });
		Assert::ExpectException<AccessToDummyException>([&] {list->getMemento(); });
	}

	TEST_METHOD(mementoAndRestore) {
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
		originalList.getSize();
		for (int i = 0; i < originalList.getSize(); i++) {
			originalList.get(i);
		}
	}

	};
}