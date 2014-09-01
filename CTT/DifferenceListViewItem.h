#ifndef _DIFFERENCELISTVIEWITEM_H
#define _DIFFERENCELISTVIEWITEM_H

#include "AbstractListViewItem.h"
#include "FrameDiff.h"

namespace view {
	class DifferenceListViewItem : public AbstractListViewItem {
		Q_OBJECT
	public:
		typedef QScopedPointer<DifferenceListViewItem> uptr;
		typedef QSharedPointer<DifferenceListViewItem> sptr;
		typedef QWeakPointer<DifferenceListViewItem> wptr;

		DifferenceListViewItem(::model::difference::FrameDiff::sptr diff, QWidget *parent = 0);

		virtual QString getIdentifier() const Q_DECL_OVERRIDE;
	};
}

#endif