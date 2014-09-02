#ifndef _DIFFERENCELISTVIEW_H
#define _DIFFERENCELISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractListView.h"
#include "SaveableList.h"
#include "FrameDiff.h"
#include "DifferenceController.h"
#include "Player.h"

namespace view {

/**
 * The DifferenceListView displays the list of the differences.
 * Every difference is shown with its parameters which are the two videos on which the difference is calculated.
 */
class DifferenceListView : public AbstractListView {
public:
    typedef QScopedPointer<DifferenceListView> uptr;
    typedef QSharedPointer<DifferenceListView> sptr;
    typedef QWeakPointer<DifferenceListView> wptr;

	DifferenceListView(::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr differences,
		::model::player::Player::sptr player, QWidget *parent = 0);

	~DifferenceListView();

	virtual void update() Q_DECL_OVERRIDE;

private:
	::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr differences;
	::model::player::Player::sptr player;
};

}  // namespace view

#endif  //_DIFFERENCELISTVIEW_H
