#if !defined(_DIFFERENCETIMELINE_H)
#define _DIFFERENCETIMELINE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractTimeline.h"

namespace view {

/**
 * The DifferenceTimeline is the visual representation of a set of differences.
 * The active differences are simply plotted as overlapping different-colored graphs.
 */
class DifferenceTimeline : public AbstractTimeline {
public:
    typedef QScopedPointer<DifferenceTimeline> uptr;
    typedef QSharedPointer<DifferenceTimeline> sptr;
    typedef QWeakPointer<DifferenceTimeline> wptr;

};

}  // namespace view

#endif  //_DIFFERENCETIMELINE_H
