#include "QObject"
#include <QtTest/QtTest>

#include "../ctt/Memento.h"
#include "CustomTestingMacros.h"
#include "SaveableList.h"
#include "UIntegerInterval.h"

class MementoTest : public QObject {
	Q_OBJECT

private:
	const QString BOOL_STRING = QString("Bool");
	const QString DOUBLE_STRING = QString("Double");
	const QString FLOAT_STRING = QString("Float");
	const QString INT_STRING = QString("Int");
	const QString U_INT_STRING = QString("UInt");
	const QString STRING_STRING = QString("String");
	const QString POINTER_STRING = QString("Pointer");
	const QString POINTER_STRING_2 = QString("Pointer2");

private slots:
	void setAndGet();
	void overwrite();
	void notPresent();
	void wrongType();
	void castingPointer();
};