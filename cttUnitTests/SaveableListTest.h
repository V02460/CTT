#include "QObject"
#include <QtTest/QtTest>

#include "../ctt/SaveableList.h"
#include "CustomTestingMacros.h"

class SaveableListTest : public QObject {
	Q_OBJECT

private slots:
	void setAndGet();
	void remove();
	void outOfBounds();
	void dummyCheck();
	void mementoAndRestore();
};