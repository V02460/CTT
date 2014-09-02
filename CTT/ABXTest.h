#pragma once
#include "Observable.h"
#include "Video.h"
#include <qobject.h>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

namespace model {

	using model::video::Video;
	using model::saveable::Memento;
	/**
	 * Implements an ABX and ABXY Test for the comparison of 2 videos.
	 */
	class ABXTest :
		public Observable, public saveable::Saveable
	{
	public:
		typedef QScopedPointer<ABXTest> uptr;
		typedef QSharedPointer<ABXTest> sptr;
		typedef QWeakPointer<ABXTest> wptr;

		/**
		 * Creates a new ABXTest for the comparison of the two submitted Videos a and b.
		 * @param a source A
		 * @param b source B
		 */
		ABXTest(Video::sptr a, Video::sptr b);

		~ABXTest();

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
		bool wasLastTrySuccessful();

		/**
		 * Returns the number of completed testing rounds since the creation or the last reset of the ABXTest.
		 * @return the number of completed testing rounds
		 */
		unsigned int getNumberOfTotalTries();

		/**
		 * Returns the number of successful guesses since the creation or the last reset of the ABXTest.
		 * @return the number of successful guesses
		 */
		unsigned int getNumberOfSuccessfulTries();

		/**
		 * Returns the number of failed guesses since the creation or the last reset of the ABXTest.
		 * @return the number of failed guesses
		 */
		unsigned int getNumberOfFailedTries();

		/**
		 * Calculates and returns the probability that the current test results or better results can be achieved without perceiving a difference in the sources, but only by indiscriminate guessing.
		 * @return the probability that the current test results or better results can be achieved without perceiving a difference in the sources
		 */
		double getGuessingChance();



		virtual Memento getMemento() const;

		virtual void restore(Memento memento);

		static model::saveable::Saveable::sptr getDummy();

		static Saveable::SaveableType getSaveableType();

	private:
		/**
		 * Creates a dummy ABXTest.
		 */
		ABXTest();

		const static QString videoAStringID;
		const static QString videoBStringID;
		const static QString xIsAStringId;
		const static QString lastTryWasSuccessfulStringId;
		const static QString triesStringId;
		const static QString successfulTriesStringId;


		void distributeVideos();
		bool identify(bool xIsAandYisB);

		unsigned long binomialCoefficient(unsigned long n, unsigned long k);

		Video::sptr a;
		Video::sptr b;
		Video::sptr x;
		Video::sptr y;

		bool xIsA;
		bool lastTryWasSuccessful;

		unsigned int tries;
		unsigned int successfulTries;
	};

}

