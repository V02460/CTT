#ifndef _FILTERLISTVIEW_H
#define _FILTERLISTVIEW_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractListView.h"
#include "FilteredVideo.h"
#include "Filter.h"
#include "FilterParam.h"
#include "FilterController.h"

namespace view {

/**
 * The FilterListView displays the list of filters in a filtered video.
 * For each filter all of its parameters are shown in a table-like view.
 * For each parameter type (String, int, bool, ...) there is a specific component (spinbox, textarea, ...) so that those
 * parameters can be easily changed by just clicking on them and adjusting its value.
 */
class FilterListView : public AbstractListView {
	Q_OBJECT

public:
    typedef QScopedPointer<FilterListView> uptr;
    typedef QSharedPointer<FilterListView> sptr;
    typedef QWeakPointer<FilterListView> wptr;

	FilterListView(::controller::FilterController::sptr filterController, QWidget *parent);

	~FilterListView();

	virtual void update() Q_DECL_OVERRIDE;

	virtual void setVideo(::model::filter::FilteredVideo::sptr newVideo) Q_DECL_OVERRIDE;
	virtual void removeVideo() Q_DECL_OVERRIDE;

public slots:
	void filterSelectionChanged();

signals:
    /**
     * This signal is emitted when the order of the filters is changed
     * so when the filter is moved from its old position to a new position.
     *
     * @param oldPos The old position of the filter.
     * @param newPos The new/desired position of the filter.
     */
    void filterMoved(int oldPos, int newPos);

	void videoChanged(::model::filter::FilteredVideo::sptr video);

	void selectedFilterChanged(::model::filter::Filter::sptr filter);
private:
	::model::filter::FilteredVideo::sptr video;
	::controller::FilterController::sptr filterController;
};

}  // namespace view

#endif  //_FILTERLISTVIEW_H
