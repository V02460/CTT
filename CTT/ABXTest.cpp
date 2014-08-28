#include "ABXTest.h"
#include <qdatetime>
#include <qmath.h>

using model::ABXTest;
using model::video::Video;

model::ABXTest::ABXTest(Video::sptr a, Video::sptr b) :
a(a),
b(b),
lastTryWasSuccessfull(false),
tries(0),
successfullTries(0)
{
	qsrand((uint)QTime::currentTime().msec());
	distributeVideos();
}

void model::ABXTest::distributeVideos()
{
	if (qrand() % 2)
	{
		x = a;
		y = b;
		xIsA = true;
	}
	else
	{
		x = b;
		y = a;
		xIsA = false;
	}

	changed();
}


void model::ABXTest::reset()
{
	lastTryWasSuccessfull = false;
	tries = 0;
	successfullTries = 0;
	distributeVideos();
}

void model::ABXTest::reset(Video::sptr newA, Video::sptr newB)
{
	a = newA;
	b = newB;
	reset();
}

Video::sptr model::ABXTest::getVideoA()
{
	return a;
}

Video::sptr model::ABXTest::getVideoB()
{
	return b;
}

Video::sptr model::ABXTest::getVideoX()
{
	return x;
}

Video::sptr model::ABXTest::getVideoY()
{
	return y;
}

bool model::ABXTest::identifyXasA()
{
	return identify(true);
}

bool model::ABXTest::identify(bool xIsAandYisB)
{
	tries++;
	bool result;

	if (xIsAandYisB == xIsA)
	{
		successfullTries++;
		lastTryWasSuccessfull = true;
		result = true;
	}
	else
	{
		lastTryWasSuccessfull = false;
		result = false;
	}
	distributeVideos();
	return result;
}

bool model::ABXTest::identifyXasB()
{
	return identify(true);
}

bool model::ABXTest::wasLastTrySuccessfull()
{
	return lastTryWasSuccessfull;
}

unsigned int model::ABXTest::getNumberOfTotalTries()
{
	return tries;
}

unsigned int model::ABXTest::getNumberOfSuccessfullTries()
{
	return successfullTries;
}

unsigned int model::ABXTest::getNumberOfFailedTries()
{
	return getNumberOfTotalTries() - getNumberOfSuccessfullTries();
}

double model::ABXTest::getGuessingChance()
{
	unsigned long sum = 0;
	for (unsigned int k = successfullTries; k <= tries; k++)
	{
		sum += binomialCoefficient(tries, k);
	}

	return sum * qPow(0.5, tries);
}

unsigned long model::ABXTest::binomialCoefficient(unsigned long n, unsigned long k)
{
	unsigned long i;
	unsigned long b;
	if (0 == k || n == k) {
		return 1;
	}
	if (k > n) {
		return 0;
	}
	if (k > (n - k)) {
		k = n - k;
	}
	if (1 == k) {
		return n;
	}
	b = 1;
	for (i = 1; i <= k; ++i) {
		b *= (n - (k - i));
		if (b < 0)
		{
			//overflow
			return -1;
		}
		b /= i;
	}
	return b;
}



ABXTest::~ABXTest()
{
}
