#ifndef _DIFFERENCELISTVIEWITEM_H
#define _DIFFERENCELISTVIEWITEM_H

#include "AbstractListViewItem.h"
#include "FrameDiff.h"
#include "Player.h"

namespace view {
	class DifferenceListViewItem : public AbstractListViewItem {
		Q_OBJECT
	public:
		typedef QScopedPointer<DifferenceListViewItem> uptr;
		typedef QSharedPointer<DifferenceListViewItem> sptr;
		typedef QWeakPointer<DifferenceListViewItem> wptr;

		DifferenceListViewItem(::model::difference::FrameDiff::sptr diff, ::model::player::Player::sptr player,QColor labelColor, QWidget *parent = 0);

		virtual QLabel* getIdentifier() const Q_DECL_OVERRIDE;
		virtual void update() Q_DECL_OVERRIDE;

		private:
			::model::difference::FrameDiff::sptr diff;
			::model::player::Player::sptr player;

			QLabel *identifierLabel;
			bool initialized;
	};
}

#endif