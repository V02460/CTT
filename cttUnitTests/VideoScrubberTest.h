#ifndef _VIDEOSRUBBERTEST_H
#define _VIDEOSRUBBERTEST_H

#include <QtTest/QtTest>

class VideoScrubberTest : public QObject 
{
	Q_OBJECT


private slots:
	void initTestCase();
	void testDummy();
	void methods();
	void saveRestore();

private:
	QSharedPointer<QOpenGLContext> testContext;
};

#endif
