#include <CppUnitTest.h>
#include <functional>

#include "../ctt/Memento.h"
#include "SaveableList.h"
#include "UIntegerInterval.h"

#include <RuntimeException.h>
#include <QMessageBox>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

	using model::saveable::Memento;
	using exception::IllegalArgumentException;
	using model::saveable::SaveableList;
	using model::saveable::Saveable;
	using exception::RuntimeException;
	using model::UIntegerInterval;

	TEST_CLASS(MementoTest) {
public:
	TEST_METHOD(setAndGet) {
		Memento memento;
		bool b = false;
		double d = .1E22;
		float f = -.1F;
		int i = 5;
		unsigned int u = 17;
		QString s = QString("RandomText");
		memento.setBool(BOOL_STRING, b);
		memento.setDouble(DOUBLE_STRING, d);
		memento.setFloat(FLOAT_STRING, f);
		memento.setInt(INT_STRING, i);
		memento.setUInt(U_INT_STRING, u);
		memento.setString(STRING_STRING, s);
		memento.getBool(BOOL_STRING);
		memento.getDouble(DOUBLE_STRING);
		memento.getFloat(FLOAT_STRING);
		memento.getInt(INT_STRING);
		memento.getUInt(U_INT_STRING);
		memento.getString(STRING_STRING);
		memento.getVariableMap().size();
		SaveableList<UIntegerInterval>::sptr list
			= QSharedPointer<SaveableList<UIntegerInterval>>(new SaveableList<UIntegerInterval>());
		UIntegerInterval::sptr interval = QSharedPointer<UIntegerInterval>(new UIntegerInterval(1, 6));
		list->insert(0, interval);
		memento.setSharedPointer(POINTER_STRING, list);
		memento.setSharedPointer(POINTER_STRING_2, interval);
		memento.getPointer(POINTER_STRING);
		memento.getPointer(POINTER_STRING_2);
		memento.getPointerMap().size();
	}

	TEST_METHOD(overwrite) {
		Memento memento;
		bool a = false;
		bool b = true;
		memento.setBool(BOOL_STRING, a);
		memento.setBool(BOOL_STRING, b);
		memento.getBool(BOOL_STRING);
		memento.getVariableMap().size();
		Saveable::sptr c = QSharedPointer<Saveable>(new SaveableList<Saveable>);
		Saveable::sptr d = QSharedPointer<Saveable>(new UIntegerInterval(3, 4));
		memento.setSharedPointer(POINTER_STRING, c);
		memento.setSharedPointer(POINTER_STRING, d);
		memento.getSharedPointer(POINTER_STRING);
		memento.getPointerMap().size();
	}

	TEST_METHOD(notPresent) {
		Memento memento;
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getBool(BOOL_STRING); });
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getDouble(DOUBLE_STRING); });
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getFloat(FLOAT_STRING); });
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getInt(INT_STRING); });
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getString(STRING_STRING); });
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getSharedPointer(POINTER_STRING); });
	}

	TEST_METHOD(wrongType) {
		Memento memento;
		memento.setString(INT_STRING, QString("Not a Number!"));
		Assert::ExpectException<IllegalArgumentException>([&] {memento.getInt(INT_STRING); });
		UIntegerInterval::sptr notAList = QSharedPointer<UIntegerInterval>(new UIntegerInterval(1, 2));
		memento.setSharedPointer(POINTER_STRING, notAList);
		memento.getSharedPointer(POINTER_STRING).dynamicCast<SaveableList<UIntegerInterval>>().isNull();
	}

	TEST_METHOD(castingPointer) {
		Memento memento;
		SaveableList<Saveable>::sptr inPointer = QSharedPointer<SaveableList<Saveable>>(new SaveableList<Saveable>());
		memento.setSharedPointer(POINTER_STRING, inPointer);
		SaveableList<Saveable>::sptr outListPointer = memento.getSharedPointer(POINTER_STRING).dynamicCast<SaveableList<Saveable>>();
		Saveable::sptr outBasicPointer1 = memento.getSharedPointer(POINTER_STRING);
		Saveable::sptr outBasicPointer2 = outListPointer.dynamicCast<Saveable>();
		outBasicPointer1;
		outListPointer->insert(0, QSharedPointer<Saveable>(UIntegerInterval::getDummy()));
	}

private:
	const QString BOOL_STRING = QString("Bool");
	const QString DOUBLE_STRING = QString("Double");
	const QString FLOAT_STRING = QString("Float");
	const QString INT_STRING = QString("Int");
	const QString U_INT_STRING = QString("UInt");
	const QString STRING_STRING = QString("String");
	const QString POINTER_STRING = QString("Pointer");
	const QString POINTER_STRING_2 = QString("Pointer2");
};
}