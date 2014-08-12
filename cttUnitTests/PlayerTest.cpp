#include "PlayerTest.h"
#include "..\CTT\YUVDataVideo.h"

using model::video::YUVDataVideo;

void PlayerTest::emptyPlayer()
{
	Player test(10);

	QVERIFY(!test.isPlaying());
	QVERIFY(!test.isLooping());

	QVERIFY(test.getScrubbers().isEmpty());

	QVERIFY(!test.hasNextFrame());
	QVERIFY(!test.hasPreviousFrame());

	QCOMPARE(test.scrubberCount(), (unsigned int)0);
	QCOMPARE(test.getVideoLength(), (unsigned int)0);
	QCOMPARE(test.getCurrentFrameNumber(), (unsigned int)0);

	QCOMPARE(test.getFPS(), 10.0);
}

void PlayerTest::playingAndLooping()
{

}

void PlayerTest::scrubberOperations()
{

}
