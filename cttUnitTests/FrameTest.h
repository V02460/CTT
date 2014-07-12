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
	void withoutImage();
	void withImageInvalid();
	void withImage();
	//TODO and cleanup test cases

private:
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;
	QImage testImage;
};

