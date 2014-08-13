#include "MementoTest.h"

#include <RuntimeException.h>
#include <QMessageBox>

using model::saveable::Memento;
using exception::IllegalArgumentException;
using model::saveable::SaveableList;
using model::saveable::Saveable;
using exception::RuntimeException;

void MementoTest::setAndGet() {
	Memento memento;

	bool b = false;
	double d = .1E22;
	float f = -.1F;
	int i = 5;
	QString s = QString("RandomText");

	memento.setBool(BOOL_STRING, b);
	memento.setDouble(DOUBLE_STRING, d);
	memento.setFloat(FLOAT_STRING, f);
	memento.setInt(INT_STRING, i);
	memento.setString(STRING_STRING, s);

	QCOMPARE(memento.getBool(BOOL_STRING), b);
	QCOMPARE(memento.getDouble(DOUBLE_STRING), d);
	QCOMPARE(memento.getFloat(FLOAT_STRING), f);
	QCOMPARE(memento.getInt(INT_STRING), i);
	QCOMPARE(memento.getString(STRING_STRING), s);

	if (memento.getVariableMap().size() != 5) {
		QFAIL("Wrong variable count.");
	}

	// TODO pointer
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
	// TODO pointer
}

void MementoTest::notPresent() {
	Memento memento;
	QEXPECT_EXCEPTION(memento.getBool(BOOL_STRING), IllegalArgumentException);
	// TODO pointer
}

void MementoTest::wrongType() {
	Memento memento;
	memento.setString(INT_STRING, QString("Not a Number!"));
	QEXPECT_EXCEPTION(memento.getInt(INT_STRING), IllegalArgumentException);
	// TODO pointer
}

void MementoTest::castingPointer() {
	// TODO weird stuff
	try {
		Memento memento;
		SaveableList<Saveable> list = SaveableList<Saveable>();
		SaveableList<Saveable>::sptr inPointer;
		memento.setSharedPointer(POINTER_STRING, inPointer);
		SaveableList<Saveable>::sptr outListPointer = memento.getSharedPointer(POINTER_STRING).dynamicCast<SaveableList<Saveable>>();
		Saveable::sptr outBasicPointer1 = memento.getSharedPointer(POINTER_STRING);
		Saveable::sptr outBasicPointer2 = outListPointer.dynamicCast<Saveable>();
		QCOMPARE(outBasicPointer1, outBasicPointer2);
	} catch (RuntimeException *e) {
		QMessageBox msgBox;
		msgBox.setWindowTitle(e->getName());
		msgBox.setText(e->getMsg());
		msgBox.exec();
	}
}