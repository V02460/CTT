#if !defined(_ABSTRACTTIMELINE_H)
#define _ABSTRACTTIMELINE_H

#include "Observer.h"
#include "Observable.h"
#include <QWidget>

namespace view {
namespace base_components {
/**
 *	The AbstracTimeline is a class to unify all used timeline implementations.
 *	It stands basically for some kind of diagram over the frames of a video
 *	and displays some kind of data that is concretized in the specific implementations.
 */
class AbstractTimeline : public Observer , public Observable , public QWidget {

private:
	SaveableList displayableComponents; /**< The list over the components that should be displayed by the timeline */
};

}  // namespace base_components
}  // namespace view

#endif  //_ABSTRACTTIMELINE_H
