#ifndef _EXTENDEDVIDEOLISTCONTROLLERTEST_H
#define _EXTENDEDVIDEOLISTCONTROLLERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>

#include "YUVDataVideo.h"

class ExtendedVideoListControllerTest : public QObject {
	Q_OBJECT

	private slots:
	void initTestCase();
	void testRun();

private:
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;
	::model::video::YUVDataVideo::sptr video1;
	::model::video::YUVDataVideo::sptr video2;

};

#endif  //_EXTENDEDVIDEOLISTCONTROLLERTEST_H