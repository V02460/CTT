#pragma once
#include "qobject.h"
#include <QtTest/QtTest>
#include "QOffscreenSurface"

class FrameTest :
	public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void withoutImageInvalid();
	void withImageInvalid();

private:
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;
};

