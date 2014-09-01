#ifndef _VIDEOLISTCONTROLLERTEST_H
#define _VIDEOLISTCONTROLLERTEST_H

#include <QtTest/QtTest>
#include <QObject>
#include <QOffscreenSurface>

#include "YUVDataVideo.h"

class VideoListControllerTest : public QObject {
	Q_OBJECT

private slots:
	void initTestCase();
	void testRun();

private:
	QSharedPointer<QOpenGLContext> testContext;
	QOffscreenSurface surface;
	::model::video::YUVDataVideo::sptr video;
};

#endif  //_VIDEOLISTCONTROLLERTEST_H