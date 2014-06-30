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

	List<QString> getAllDiffIDs();
	FrameDiff createDiff(QString id, Video video1, Video video2);
};

}  // namespace difference
}  // namespace model

#endif  //_DIFFERENCEFACTORY_H
