#pragma once
#include "Observable.h"
#include "Video.h"
namespace model {

	using model::video::Video;

	class ABXTest :
		public Observable
	{
	public:
		ABXTest(Video::sptr a, Video::sptr b);
		~ABXTest();

		void reset();
		void reset(Video::sptr newA, Video::sptr newB);
		Video::sptr getVideoA();
		Video::sptr getVideoB();
		Video::sptr getVideoX();

		//not strictly necessary for ABX testing
		Video::sptr getVideoY();
		bool identifyXasA();
		bool identifyXasB();

		bool wasLastTrySuccessfull();

		unsigned int getNumberOfTotalTries();
		unsigned int getNumberOfSuccessfullTries();
		unsigned int getNumberOfFailedTries();

		double getGuessingChance();

	private:
		void distributeVideos();
		bool identify(bool xIsAandYisB);

		unsigned long binomialCoefficient(unsigned long n, unsigned long k);

		Video::sptr a;
		Video::sptr b;
		Video::sptr x;
		Video::sptr y;

		bool xIsA;
		bool lastTryWasSuccessfull;

		unsigned int tries;
		unsigned int successfullTries;
	};

}

