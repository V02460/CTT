#if !defined(_DIFFERENCEFACTORY_H)
#define _DIFFERENCEFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "FrameDiff.h"
#include "Video.h"
#include "PixelDiff.h"

namespace model {
namespace difference {

class DifferenceFactory {
public:
	typedef QScopedPointer<DifferenceFactory> uptr;
	typedef QSharedPointer<DifferenceFactory> sptr;
	typedef QWeakPointer<DifferenceFactory> wptr;

	QList<QString> getAllFrameDiffIDs();
	QList<QString> getAllPixelDiffIDs();
	FrameDiff createFrameDiff(QString id, model::video::Video video1, model::video::Video video2);
	PixelDiff createPixelDiff(QString id, model::video::Video video1, model::video::Video video2);
};

}  // namespace difference
}  // namespace model

#endif  //_DIFFERENCEFACTORY_H
