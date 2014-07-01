#if !defined(_ABSTRACTTIMELINE_H)
#define _ABSTRACTTIMELINE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>

#include "Observer.h"
#include "Observable.h"

namespace view {
/**
 * The AbstracTimeline is a class to unify all used timeline implementations.
 * It stands basically for some kind of diagram over the frames of a video
 * and displays some kind of data that is concretized in the specific implementations.
 */
class AbstractTimeline : public ::model::Observer , public ::model::Observable , public QWidget {
public:
    typedef QScopedPointer<AbstractTimeline> uptr;
    typedef QSharedPointer<AbstractTimeline> sptr;
    typedef QWeakPointer<AbstractTimeline> wptr;

private:
    //SaveableList displayableComponents; /**< The list over the components that should be displayed by the timeline */
};

}  // namespace view

#endif  //_ABSTRACTTIMELINE_H
