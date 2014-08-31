#ifndef _DIFFERENCELISTVIEWITEM_H
#define _DIFFERENCELISTVIEWITEM_H

#include "AbstractListViewItem.h"

namespace view {
	class DifferenceListViewItem : public AbstractListViewItem {
		Q_OBJECT
	public:
		typedef QScopedPointer<DifferenceListViewItem> uptr;
		typedef QSharedPointer<DifferenceListViewItem> sptr;
		typedef QWeakPointer<DifferenceListViewItem> wptr;



	};
}

#endif