#ifndef _ABXCONTROLLER_H
#define _ABXCONTROLLER_H

#include "Video.h"
#include "ABXTest.h"
#include <QObject>

namespace controller{

	using ::model::video::Video;
	using ::model::ABXTest;

	class ABXController: public QObject
	{
		Q_OBJECT
	public:
		typedef QScopedPointer<ABXController> uptr;
		typedef QSharedPointer<ABXController> sptr;
		typedef QWeakPointer<ABXController> wptr;

		ABXController(Video::sptr a, Video::sptr b);
		~ABXController();;

		ABXTest::sptr getABXTest() const;

	public slots:
		void reset();
		void reset(Video::sptr newA, Video::sptr newB);
		void xIsA();
		void xIsB();

	private:
		::model::ABXTest::sptr test;
	};
}


#endif

