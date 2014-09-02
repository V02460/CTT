#include "ABXTest.h"
#include <qdatetime>
#include <qmath.h>

using model::ABXTest;
using model::video::Video;
using exception::AccessToDummyException;

const QString ABXTest::videoAStringID("videoA");
const QString ABXTest::videoBStringID("videoB");
const QString ABXTest::xIsAStringId("xIsA");
const QString ABXTest::lastTryWasSuccessfulStringId("lastTrySuccessfull");
const QString ABXTest::triesStringId("tries");
const QString ABXTest::successfulTriesStringId("successfullTries");

model::ABXTest::ABXTest(Video::sptr a, Video::sptr b) :
a(a),
b(b),
lastTryWasSuccessful(false),
tries(0),
successfulTries(0)
{
	qsrand((uint)QTime::currentTime().msec());
	distributeVideos();
}

model::ABXTest::ABXTest()
{
	isDummyFlag = true;
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
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to reset a dummy ABXTest.");
	}
	lastTryWasSuccessful = false;
	tries = 0;
	successfulTries = 0;
	distributeVideos();
}

void model::ABXTest::reset(Video::sptr newA, Video::sptr newB)
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to reset a dummy ABXTest.");
	}
	a = newA;
	b = newB;
	reset();
}

Video::sptr model::ABXTest::getVideoA()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get a video from a dummy ABXTest.");
	}
	return a;
}

Video::sptr model::ABXTest::getVideoB()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get a video from a dummy ABXTest.");
	}
	return b;
}

Video::sptr model::ABXTest::getVideoX()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get a video from a dummy ABXTest.");
	}
	return x;
}

Video::sptr model::ABXTest::getVideoY()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get a video from a dummy ABXTest.");
	}
	return y;
}

bool model::ABXTest::identifyXasA()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to use a dummy ABXTest.");
	}
	return identify(true);
}

bool model::ABXTest::identify(bool xIsAandYisB)
{
	tries++;
	bool result;

	if (xIsAandYisB == xIsA)
	{
		successfulTries++;
		lastTryWasSuccessful = true;
		result = true;
	}
	else
	{
		lastTryWasSuccessful = false;
		result = false;
	}
	distributeVideos();
	return result;
}

bool model::ABXTest::identifyXasB()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to use a dummy ABXTest.");
	}
	return identify(false);
}

bool model::ABXTest::wasLastTrySuccessful()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to ask a dummy ABXTest whether the last try was successful.");
	}
	return lastTryWasSuccessful;
}

unsigned int model::ABXTest::getNumberOfTotalTries()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get the number of tries from a dummy ABXTest.");
	}
	return tries;
}

unsigned int model::ABXTest::getNumberOfSuccessfulTries()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get the number of successful tries from a dummy ABXTest.");
	}
	return successfulTries;
}

unsigned int model::ABXTest::getNumberOfFailedTries()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get the number of failed tries from a dummy ABXTest.");
	}
	return getNumberOfTotalTries() - getNumberOfSuccessfulTries();
}

double model::ABXTest::getGuessingChance()
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get the guessing chance from a dummy ABXTest.");
	}

	unsigned long sum = 0;
	for (unsigned int k = successfulTries; k <= tries; k++)
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

model::saveable::Saveable::sptr ABXTest::getDummy()
{
	return Saveable::sptr(new ABXTest());
}

model::saveable::Memento ABXTest::getMemento() const
{
	if (isDummy())
	{
		throw new AccessToDummyException("Tried to get a memento from a dummy ABXTest.");
	}

	Memento memento;
	memento.setSharedPointer(videoAStringID, a);
	memento.setSharedPointer(videoBStringID, b);
	memento.setBool(xIsAStringId, xIsA);
	memento.setBool(lastTryWasSuccessfulStringId, lastTryWasSuccessful);
	memento.setUInt(triesStringId, tries);
	memento.setUInt(successfulTriesStringId, successfulTries);
	return memento;
}

void model::ABXTest::restore(Memento memento)
{
	a = memento.getSharedPointer(videoAStringID).dynamicCast<Video>();
	b = memento.getSharedPointer(videoBStringID).dynamicCast<Video>();
	xIsA = memento.getBool(xIsAStringId);
	if (xIsA)
	{
		x = a;
		y = b;
	}
	else
	{
		x = b;
		y = a;
	}
	lastTryWasSuccessful = memento.getBool(lastTryWasSuccessfulStringId);
	tries = memento.getUInt(triesStringId);
	successfulTries = memento.getUInt(successfulTriesStringId);
	isDummyFlag = false;
}

model::saveable::Saveable::SaveableType ABXTest::getSaveableType()
{
	return model::saveable::Saveable::aBXTest;
}


ABXTest::~ABXTest()
{
}
