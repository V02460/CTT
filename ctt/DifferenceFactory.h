#if !defined(_DIFFERENCEFACTORY_H)
#define _DIFFERENCEFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "FrameDiff.h"
#include "Video.h"

namespace model {
namespace difference {

class DifferenceFactory {
public:
	typedef QScopedPointer<DifferenceFactory> uptr;
	typedef QSharedPointer<DifferenceFactory> sptr;
	typedef QWeakPointer<DifferenceFactory> wptr;

	static QList<QString> getAllDiffIDs();
	static FrameDiff::sptr createDiff(QString id, const video::Video &video1, const video::Video &video2);

private:
	DifferenceFactory() {}
};

}  // namespace difference
}  // namespace model

#endif  //_DIFFERENCEFACTORY_H
