#ifndef _FRAMETEST_H
#define _FRAMETEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>
#include <Qtest>

class FrameTest : public QObject {
	Q_OBJECT

private slots:
	void initTestCase();
	void withoutImageInvalid();
	void withoutImage();
	void withImageInvalid();
	void withImage();

private:
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;
	QImage testImage;
};

#endif