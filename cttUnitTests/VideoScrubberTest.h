#ifndef _VIDEOSRUBBERTEST_H
#define _VIDEOSRUBBERTEST_H

#include <QtTest/QtTest>
#include "QOffscreenSurface"

class VideoScrubberTest : public QObject {
	Q_OBJECT

public:
    VideoScrubberTest();

private slots:
	void initTestCase();
	void testDummy();
	void methods();

	//TODO ObserverObservableStuff when ready kiuzfzrdhrdufjf

private:
	QOffscreenSurface surface;
	QSharedPointer<QOpenGLContext> testContext;
};

#endif
