#pragma once
#include "Observable.h"
#include "Video.h"
namespace model {

	using model::video::Video;
	/**
	 * Implements an ABX and ABXY Test for the comparison of 2 videos.
	 */
	class ABXTest :
		public Observable
	{
	public:
		/**
		 * Creates a new ABXTest for the comparison of the two submitted Videos a and b.
		 * @param a source A
		 * @param b source B
		 */
		ABXTest(Video::sptr a, Video::sptr b);

		/**
		 * Resets the results of the ABXTest (i.e. as if it was newly created).
		 */
		void reset();

		/**
		 * Resets the results of the ABXTest and the videos used for comparison (i.e. as if it was newly created).
		 * @param a source A
		 * @param b source B
		 */
		void reset(Video::sptr newA, Video::sptr newB);

		/**
		 * Gets video A, as it was set in the constructor or the reset method.
		 * @return video A
		 */
		Video::sptr getVideoA();

		/**
		 * Gets video B, as it was set in the constructor or the reset method.
		 * @return video B
		 */
		Video::sptr getVideoB();

		/**
		 * Gets video X, which is randomly and indiscriminatingly selected from A and B for every testing round.
		 * @return video X
		 */
		Video::sptr getVideoX();

		/**
		 * Gets video Y, which is always the Video of A and B which isn't X. This isn't strictly necessary for valid ABX testing.
		 * @return video Y
		 */
		Video::sptr getVideoY();

		/**
		 * For the current testing round, guesses that X is A. This starts the next testing round.
		 * @return true only if X is A
		 */
		bool identifyXasA();

		/**
		 * For the current testing round, guesses that X is B. This starts the next testing round.
		 * @return true only if X is B
		 */
		bool identifyXasB();

		/**
		 * Returns whether the last guess was correct.
		 * @return true only if the last guess was correct
		 */
		bool wasLastTrySuccessfull();

		/**
		 * Returns the number of completed testing rounds since the creation or the last reset of the ABXTest.
		 * @return the number of completed testing rounds
		 */
		unsigned int getNumberOfTotalTries();

		/**
		 * Returns the number of successfull guesses since the creation or the last reset of the ABXTest.
		 * @return the number of successfull guesses
		 */
		unsigned int getNumberOfSuccessfullTries();

		/**
		 * Returns the number of failed guesses since the creation or the last reset of the ABXTest.
		 * @return the number of failed guesses
		 */
		unsigned int getNumberOfFailedTries();

		/**
		 * Calculates and returns the probability that the current test results can be achieved without perceiving a difference in the sources, but only by indiscriminate guessing.
		 * @return the probability that the current test results can be achieved without perceiving a difference in the sources
		 */
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

