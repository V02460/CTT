#pragma once

#include <QtTest/QtTest>
#include <QObject>

class ABXTesttest:
	public QObject
{
	Q_OBJECT

private slots:
	void testDummy();
	void methods();
	void saveRestore();
};

