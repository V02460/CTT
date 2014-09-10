#include <CppUnitTest.h>
#include <functional>

#pragma once

#include "ABXTest.h"
#include "YUVDataVideo.h"
#include "GlobalContext.h"
#include "Video.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ctt_unit_tests {

using model::ABXTest;
using model::video::Video;
using model::saveable::Memento;

TEST_CLASS(ABXTesttest) {

TEST_METHOD(testDummy) {
	ABXTest::getDummy()->isDummy();
}

TEST_METHOD(methods) {
	model::video::YUVDataVideo::sptr yuvA(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get()));
	model::video::YUVDataVideo::sptr yuvB(new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, model::GlobalContext::get()));

	model::video::Video::sptr a = yuvA.dynamicCast<Video>();
	model::video::Video::sptr b = yuvB.dynamicCast<Video>();

	ABXTest test(a, b);

	a = test.getVideoA();
	b = test.getVideoB();
	test.wasLastTrySuccessful();
	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.getGuessingChance();

	if (test.getVideoX() == test.getVideoA())
	{
		test.getVideoY() = b;
		test.identifyXasA();
	}
	else
	{
		test.getVideoX() = b;
		test.getVideoY() = a;
		test.identifyXasB();
	}

	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.wasLastTrySuccessful();
	test.getGuessingChance();

	if (test.getVideoX() == test.getVideoA())
	{
		test.identifyXasB();
	}
	else
	{
		test.identifyXasA();
	}

	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.wasLastTrySuccessful();
	test.getGuessingChance();

	if (test.getVideoX() == test.getVideoA())
	{
		test.identifyXasA();
	}
	else
	{
		test.identifyXasB();
	}

	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.wasLastTrySuccessful();
	test.getGuessingChance();

	if (test.getVideoX() == test.getVideoA())
	{
		test.identifyXasA();
	}
	else
	{
		test.identifyXasB();
	}

	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.wasLastTrySuccessful();
	test.getGuessingChance();
	
	test.reset();
	a = test.getVideoA();
	b = test.getVideoB();
	test.wasLastTrySuccessful();
	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.getGuessingChance();

	model::video::YUVDataVideo::sptr yuvA2(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get()));
	model::video::YUVDataVideo::sptr yuvB2(new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, model::GlobalContext::get()));
	model::video::Video::sptr a2 = yuvA2.dynamicCast<Video>();
	model::video::Video::sptr b2 = yuvB2.dynamicCast<Video>();

	test.reset(a2, b2);
	a2 = test.getVideoA();
	b2 = test.getVideoB();
	test.wasLastTrySuccessful();
	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.getGuessingChance();
}

TEST_METHOD(saveRestore) {
	model::video::YUVDataVideo::sptr yuvA(new model::video::YUVDataVideo("resources/Videos/YUV444/squirrel-720x576-444P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV444, model::GlobalContext::get()));
	model::video::YUVDataVideo::sptr yuvB(new model::video::YUVDataVideo("resources/Videos/YUV422/squirrel-720x576-422P.yuv", QSize(720, 576), 24, model::video::YUVType::YUV422, model::GlobalContext::get()));

	model::video::Video::sptr a = yuvA.dynamicCast<Video>();
	model::video::Video::sptr b = yuvB.dynamicCast<Video>();

	ABXTest test(a, b);

	for (int i = 0; i < 3; i++)
	{
		if (test.getVideoX() == test.getVideoA())
		{
			test.identifyXasA();
		}
		else
		{
			test.identifyXasB();
		}
	}

	if (test.getVideoX() == test.getVideoA())
	{
		test.identifyXasB();
	}
	else
	{
		test.identifyXasA();
	}

	model::saveable::Saveable::sptr saveableDummy = ABXTest::getDummy();

	ABXTest::sptr dummy = saveableDummy.dynamicCast<ABXTest>();

	Memento memento = test.getMemento();

	dummy->restore(memento);
	dummy->getNumberOfTotalTries();
	dummy->getNumberOfSuccessfulTries();
	dummy->getNumberOfFailedTries();
	dummy->wasLastTrySuccessful();
	dummy->getGuessingChance();

	test.identifyXasA();
	test.restore(memento);
	test.getNumberOfTotalTries();
	test.getNumberOfSuccessfulTries();
	test.getNumberOfFailedTries();
	test.wasLastTrySuccessful();
	test.getGuessingChance();	
}

};
}