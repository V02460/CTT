#ifndef _DIFFERENCELISTVIEW_H
#define _DIFFERENCELISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractListView.h"
#include "SaveableList.h"
#include "FrameDiff.h"
#include "DifferenceController.h"

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
		::controller::DifferenceController::sptr differenceController, QWidget *parent = 0);

	virtual void update() Q_DECL_OVERRIDE;
};

}  // namespace view

#endif  //_DIFFERENCELISTVIEW_H
