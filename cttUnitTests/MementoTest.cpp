#include "MementoTest.h"

#include <RuntimeException.h>
#include <QMessageBox>

using model::saveable::Memento;
using exception::IllegalArgumentException;
using model::saveable::SaveableList;
using model::saveable::Saveable;
using exception::RuntimeException;
using model::UIntegerInterval;

void MementoTest::setAndGet() {
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
	QCOMPARE(memento.getBool(BOOL_STRING), b);
	QCOMPARE(memento.getDouble(DOUBLE_STRING), d);
	QCOMPARE(memento.getFloat(FLOAT_STRING), f);
	QCOMPARE(memento.getInt(INT_STRING), i);
	QCOMPARE(memento.getUInt(U_INT_STRING), u);
	QCOMPARE(memento.getString(STRING_STRING), s);
	if (memento.getVariableMap().size() != 6) {
		QFAIL("Wrong variable count.");
	}
	SaveableList<UIntegerInterval>::sptr list
		= QSharedPointer<SaveableList<UIntegerInterval>>(new SaveableList<UIntegerInterval>());
	UIntegerInterval::sptr interval = QSharedPointer<UIntegerInterval>(new UIntegerInterval(1, 6));
	list->insert(0, interval);
	memento.setSharedPointer(POINTER_STRING, list);
	memento.setSharedPointer(POINTER_STRING_2, interval);
	if (memento.getPointer(POINTER_STRING) != list || memento.getPointer(POINTER_STRING_2) != interval) {
		QFAIL("Memento broke a Pointer.");
	}
	if (memento.getPointerMap().size() != 2) {
		QFAIL("Wrong pointer count.");
	}
}

void MementoTest::overwrite() {
	Memento memento;
	bool a = false;
	bool b = true;
	memento.setBool(BOOL_STRING, a);
	memento.setBool(BOOL_STRING, b);
	QCOMPARE(memento.getBool(BOOL_STRING), b);
	if (memento.getVariableMap().size() != 1) {
		QFAIL("Wrong variable count.");
	}
	Saveable::sptr c = QSharedPointer<Saveable>(new SaveableList<Saveable>);
	Saveable::sptr d = QSharedPointer<Saveable>(new UIntegerInterval(3, 4));
	memento.setSharedPointer(POINTER_STRING, c);
	memento.setSharedPointer(POINTER_STRING, d);
	QCOMPARE(memento.getSharedPointer(POINTER_STRING), d);
	if (memento.getPointerMap().size() != 1) {
		QFAIL("Wrong pointer count.");
	}
}

void MementoTest::notPresent() {
	Memento memento;
	QEXPECT_EXCEPTION(memento.getBool(BOOL_STRING), IllegalArgumentException);
	QEXPECT_EXCEPTION(memento.getDouble(DOUBLE_STRING), IllegalArgumentException);
	QEXPECT_EXCEPTION(memento.getFloat(FLOAT_STRING), IllegalArgumentException);
	QEXPECT_EXCEPTION(memento.getInt(INT_STRING), IllegalArgumentException);
	QEXPECT_EXCEPTION(memento.getString(STRING_STRING), IllegalArgumentException);
	QEXPECT_EXCEPTION(memento.getSharedPointer(POINTER_STRING), IllegalArgumentException);
}

void MementoTest::wrongType() {
	Memento memento;
	memento.setString(INT_STRING, QString("Not a Number!"));
	QEXPECT_EXCEPTION(memento.getInt(INT_STRING), IllegalArgumentException);
	UIntegerInterval::sptr notAList = QSharedPointer<UIntegerInterval>(new UIntegerInterval(1, 2));
	memento.setSharedPointer(POINTER_STRING, notAList);
	if (!memento.getSharedPointer(POINTER_STRING).dynamicCast<SaveableList<UIntegerInterval>>().isNull()) {
		QFAIL("Magic just happened! Dynamic cast worked for weird reasons.");
	}
}

void MementoTest::castingPointer() {
	Memento memento;
	SaveableList<Saveable>::sptr inPointer = QSharedPointer<SaveableList<Saveable>>(new SaveableList<Saveable>());
	memento.setSharedPointer(POINTER_STRING, inPointer);
	SaveableList<Saveable>::sptr outListPointer = memento.getSharedPointer(POINTER_STRING).dynamicCast<SaveableList<Saveable>>();
	Saveable::sptr outBasicPointer1 = memento.getSharedPointer(POINTER_STRING);
	Saveable::sptr outBasicPointer2 = outListPointer.dynamicCast<Saveable>();
	QCOMPARE(outBasicPointer1, outBasicPointer2);
	outListPointer->insert(0, QSharedPointer<Saveable>(UIntegerInterval::getDummy()));
}