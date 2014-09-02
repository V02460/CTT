#ifndef _VIDEOLISTCONTROLLERTEST_H
#define _VIDEOLISTCONTROLLERTEST_H

#include <QtTest/QtTest>
#include <QObject>

#include "YUVDataVideo.h"

class VideoListControllerTest : public QObject {
	Q_OBJECT

private slots:
	void initTestCase();
	void testRun();

private:
	QSharedPointer<QOpenGLContext> testContext;
	::model::video::YUVDataVideo::sptr video;
};

#endif  //_VIDEOLISTCONTROLLERTEST_H