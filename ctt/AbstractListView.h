#if !defined(_ABSTRACTLISTVIEW_H)
#define _ABSTRACTLISTVIEW_H

namespace view {
namespace base_components {

#include "Observer.h"
#include "Observable.h"

class AbstractListView : public Observer, public Observable {
};

}  // namespace base_components
}  // namespace view

#endif  //_ABSTRACTLISTVIEW_H
