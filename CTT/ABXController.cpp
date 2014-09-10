#include "ABXController.h"
#include "ABXTest.h"

using model::video::Video;
using model::ABXTest;

controller::ABXController::ABXController(Video::sptr a, Video::sptr b)
{
	test.reset((new ABXTest(a, b)));
}

controller::ABXController::~ABXController()
{

}

ABXTest::sptr controller::ABXController::getABXTest() const
{
	return test;
}

void controller::ABXController::reset()
{
	test->reset();
}

void controller::ABXController::reset(Video::sptr newA, Video::sptr newB) {
	test->reset(newA, newB);
}

void controller::ABXController::xIsA()
{
	test->identifyXasA();
}

void controller::ABXController::xIsB()
{
	test->identifyXasB();
}

