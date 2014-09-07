#include "ABXTesttest.h"
#include "ABXTest.h"
#include "YUVDataVideo.h"
#include "GlobalContext.h"
#include "Video.h"

using model::ABXTest;
using model::video::Video;
using model::saveable::Memento;

void ABXTesttest::testDummy()
{
	QVERIFY(ABXTest::getDummy()->isDummy());
}

void ABXTesttest::methods()
{
	model::video::YUVDataVideo::sptr yuvA(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get()));
	model::video::YUVDataVideo::sptr yuvB(new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, model::GlobalContext::get()));

	model::video::Video::sptr a = yuvA.dynamicCast<Video>();
	model::video::Video::sptr b = yuvB.dynamicCast<Video>();

	ABXTest test(a, b);

	QVERIFY(a = test.getVideoA());
	QVERIFY(b = test.getVideoB());
	QVERIFY(!test.wasLastTrySuccessful());
	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)0);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)0);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)0);
	QCOMPARE(test.getGuessingChance(), 1.0);

	if (test.getVideoX() == test.getVideoA())
	{
		QVERIFY(test.getVideoY() = b);
		QVERIFY(test.identifyXasA());
	}
	else
	{
		QVERIFY(test.getVideoX() = b);
		QVERIFY(test.getVideoY() = a);
		QVERIFY(test.identifyXasB());
	}

	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)1);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)1);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)0);
	QVERIFY(test.wasLastTrySuccessful());
	QCOMPARE(test.getGuessingChance(), 0.5);

	if (test.getVideoX() == test.getVideoA())
	{
		QVERIFY(!test.identifyXasB());
	}
	else
	{
		QVERIFY(!test.identifyXasA());
	}

	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)2);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)1);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)1);
	QVERIFY(!test.wasLastTrySuccessful());
	QCOMPARE(test.getGuessingChance(), 0.75);

	if (test.getVideoX() == test.getVideoA())
	{
		QVERIFY(test.identifyXasA());
	}
	else
	{
		QVERIFY(test.identifyXasB());
	}

	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)3);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)2);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)1);
	QVERIFY(test.wasLastTrySuccessful());
	QCOMPARE(test.getGuessingChance(), 0.5);

	if (test.getVideoX() == test.getVideoA())
	{
		QVERIFY(test.identifyXasA());
	}
	else
	{
		QVERIFY(test.identifyXasB());
	}

	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)4);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)3);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)1);
	QVERIFY(test.wasLastTrySuccessful());
	QCOMPARE(test.getGuessingChance(), 0.3125);
	
	test.reset();
	QVERIFY(a = test.getVideoA());
	QVERIFY(b = test.getVideoB());
	QVERIFY(!test.wasLastTrySuccessful());
	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)0);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)0);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)0);
	QCOMPARE(test.getGuessingChance(), 1.0);

	model::video::YUVDataVideo::sptr yuvA2(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get()));
	model::video::YUVDataVideo::sptr yuvB2(new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, model::GlobalContext::get()));
	model::video::Video::sptr a2 = yuvA2.dynamicCast<Video>();
	model::video::Video::sptr b2 = yuvB2.dynamicCast<Video>();

	test.reset(a2, b2);
	QVERIFY(a2 = test.getVideoA());
	QVERIFY(b2 = test.getVideoB());
	QVERIFY(!test.wasLastTrySuccessful());
	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)0);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)0);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)0);
	QCOMPARE(test.getGuessingChance(), 1.0);
}

void ABXTesttest::saveRestore()
{
	model::video::YUVDataVideo::sptr yuvA(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get()));
	model::video::YUVDataVideo::sptr yuvB(new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, model::GlobalContext::get()));

	model::video::Video::sptr a = yuvA.dynamicCast<Video>();
	model::video::Video::sptr b = yuvB.dynamicCast<Video>();

	ABXTest test(a, b);

	for (int i = 0; i < 3; i++)
	{
		if (test.getVideoX() == test.getVideoA())
		{
			QVERIFY(test.identifyXasA());
		}
		else
		{
			QVERIFY(test.identifyXasB());
		}
	}

	if (test.getVideoX() == test.getVideoA())
	{
		QVERIFY(!test.identifyXasB());
	}
	else
	{
		QVERIFY(!test.identifyXasA());
	}

	model::saveable::Saveable::sptr saveableDummy = ABXTest::getDummy();

	ABXTest::sptr dummy = saveableDummy.dynamicCast<ABXTest>();

	Memento memento = test.getMemento();

	dummy->restore(memento);
	QCOMPARE(dummy->getNumberOfTotalTries(), (unsigned int)4);
	QCOMPARE(dummy->getNumberOfSuccessfulTries(), (unsigned int)3);
	QCOMPARE(dummy->getNumberOfFailedTries(), (unsigned int)1);
	QVERIFY(!dummy->wasLastTrySuccessful());
	QCOMPARE(dummy->getGuessingChance(), 0.3125);

	test.identifyXasA();
	test.restore(memento);
	QCOMPARE(test.getNumberOfTotalTries(), (unsigned int)4);
	QCOMPARE(test.getNumberOfSuccessfulTries(), (unsigned int)3);
	QCOMPARE(test.getNumberOfFailedTries(), (unsigned int)1);
	QVERIFY(!test.wasLastTrySuccessful());
	QCOMPARE(test.getGuessingChance(), 0.3125);	
}
