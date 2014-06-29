#if !defined(_ABSTRACTLISTVIEW_H)
#define _ABSTRACTLISTVIEW_H

namespace view {
namespace base_components {

#include "Observer.h"
#include "Observable.h"

/**
*	The AbstracListView is a class to unify all used list view implementations.
*	It stands basically for some kind of list and displays all the elements of that list
*	in a way that is concretized in the specific implementation.
*/
class AbstractListView : public Observer, public Observable {

private:
	SaveableList diplayableComponents; /**< The list over the components that should be displayed by the list view */
};

}  // namespace base_components
}  // namespace view

#endif  //_ABSTRACTLISTVIEW_H
