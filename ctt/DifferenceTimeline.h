#if !defined(_DIFFERENCETIMELINE_H)
#define _DIFFERENCETIMELINE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "AbstractTimeline.h"

namespace view {
namespace base_components {

/**
 *	The DifferenceTimeline is the visual representation of a set of differences.
 *	The active differences are simply plotted as overlapping different-colored graphs.
 */
class DifferenceTimeline : public AbstractTimeline {
};

}  // namespace base_components
}  // namespace view

#endif  //_DIFFERENCETIMELINE_H
