#ifndef _FILTERTIMELINE_H
#define _FILTERTIMELINE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QTableWidget>
#include <QPushButton>
#include <QSpinBox>

#include "AbstractTimeline.h"
#include "Filter.h"
#include "FilterTimelineItem.h"
#include "FilterController.h"

namespace view {

/**
 * The FilterTimeline displays the filter intervals of ervery filter of a filteredVideo.
 * Each interval is painted as a bar which is moveable within the video.
 */
class FilterTimeline : public AbstractTimeline {
	Q_OBJECT
public:
    typedef QScopedPointer<FilterTimeline> uptr;
    typedef QSharedPointer<FilterTimeline> sptr;
    typedef QWeakPointer<FilterTimeline> wptr;

	FilterTimeline(::controller::FilterController::sptr filterController, QWidget *parent = 0);

	virtual void update() Q_DECL_OVERRIDE;

public slots:
	void setFilter(::model::filter::Filter::sptr filter);

	void intervalRemoved(int id);
	void intervalChanged(::model::UIntegerInterval::sptr interval);
	void btnAddIntervalClicked();

signals:
	void removeInterval(::model::filter::Filter::sptr filter, int id);
	void activateInterval(::model::filter::Filter::sptr filter, ::model::UIntegerInterval::sptr interval);

private:
	void setupUi();

	::model::filter::Filter::sptr filter;
	QList<FilterTimelineItem::sptr> items;
	::controller::FilterController::sptr filterController;
	QTableWidget *intervalTable;
	QPushButton *btnAddInterval;
	QSpinBox *spinboxIntervalStart;
	QSpinBox *spinBoxIntervalEnd;
};

}  // namespace view

#endif  //_FILTERTIMELINE_H