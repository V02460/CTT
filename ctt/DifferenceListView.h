#if !defined(_DIFFERENCELISTVIEW_H)
#define _DIFFERENCELISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "AbstractListView.h"

namespace view {
namespace base_components {

/**
 *	The DifferenceListView displays the list of the differences.
 *	Every difference is shown with its parameters which are the two videos on which the difference is calculated.
 */
class DifferenceListView : public AbstractListView {
};

}  // namespace base_components
}  // namespace view

#endif  //_DIFFERENCELISTVIEW_H
