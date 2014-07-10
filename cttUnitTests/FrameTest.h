#pragma once
#include "qobject.h"
#include <QtTest/QtTest>

class FrameTest :
	public QObject
{
	Q_OBJECT

private slots:
	void withoutImageInvalid();
	void withImageInvalid();
};

