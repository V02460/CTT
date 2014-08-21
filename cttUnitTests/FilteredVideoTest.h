#pragma once
#include <QtTest/QtTest>
#include <qoffscreensurface.h>

class FilteredVideoTest : public QObject
{
	Q_OBJECT

private slots:
	void initTestCase();
	void dummyTest();
	void filterOperations();

private:
	QOffscreenSurface surface;
	QSharedPointer<QOpenGLContext> testContext;
};

