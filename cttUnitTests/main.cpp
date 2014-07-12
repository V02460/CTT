#include <QApplication>
#include <QtTest/QTest>

#include "VideoMetadataTest.h"
#include "FrameTest.h"
#include "VideoScrubberTest.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	VideoMetadataTest videoMetadataTest;
	QTest::qExec(&videoMetadataTest, argc, argv);

	FrameTest frameTest;
	QTest::qExec(&frameTest, argc, argv);

	VideoScrubberTest videoScrubberTest;
	QTest::qExec(&videoScrubberTest, argc, argv);

	return 0;
}
