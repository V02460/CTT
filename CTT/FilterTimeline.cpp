#include "FilterTimeline.h"

#include <QVBoxLayout>

#include "UIntegerInterval.h"

using ::model::filter::Filter;
using ::model::UIntegerInterval;

namespace view {
	FilterTimeline::FilterTimeline(::controller::FilterController::sptr filterController, QWidget *parent) : AbstractTimeline(parent), intervalTable(), filter(), items(), filterController(filterController) {
		intervalTable->setColumnCount(3);
		intervalTable->setRowCount(0);

		spinboxIntervalStart = new QSpinBox(intervalTable);
		spinboxIntervalStart->setMinimum(0);
		spinboxIntervalStart->setMaximum(0);
		
		spinBoxIntervalEnd = new QSpinBox(intervalTable);
		spinBoxIntervalEnd->setMinimum(0);
		spinboxIntervalStart->setMaximum(0);

		btnAddInterval = new QPushButton(intervalTable);
		btnAddInterval->setText(tr("ADD_INTERVAL"));
		QObject::connect(btnAddInterval, SIGNAL(clicked(bool)), this, SLOT(btnAddIntervalClicked()));

		QVBoxLayout *layout = new QVBoxLayout(this);
		layout->addWidget(intervalTable);

		//TODO Connect mit dem FilterController zum Intervall ändern und btnAddInterval aktivieren
		btnAddInterval->setEnabled(false);
		setupUi();
	}

	void FilterTimeline::update() {
		intervalTable->clear();
		intervalTable->setRowCount(0);
		items.clear();

		QList<UIntegerInterval::sptr> intervals = filter->getListOfActiveIntervals();
		for (int i = 0; i < intervals.size(); i++) {
			FilterTimelineItem::sptr item(new FilterTimelineItem(i, intervals.value(i), filter->getFrameCount()));
			QObject::connect(item.data(), SIGNAL(intervalRemoveClicked(int)), this, SLOT(intervalRemoved(int)));
			QObject::connect(item.data(), SIGNAL(intervalChanged(::model::UIntegerInterval::sptr)),
				this, SLOT(intervalChanged(::model::UIntegerInterval::sptr)));
			items.append(item);
		}

		spinboxIntervalStart->setMaximum(filter->getFrameCount());
		spinBoxIntervalEnd->setMaximum(filter->getFrameCount());

		setupUi();
	}

	void FilterTimeline::setupUi() {
		for (int i = 0; i < items.size(); i++) {
			intervalTable->setCellWidget(i, 0, items.at(i)->getIntervalStartSpinBox());
			intervalTable->setCellWidget(i, 1, items.at(i)->getIntervalEndSpinBox());
			intervalTable->setCellWidget(i, 2, items.at(i)->getRemoveIntervalButton());
		}

		intervalTable->setCellWidget(intervalTable->rowCount(), 0, spinboxIntervalStart);
		intervalTable->setCellWidget(intervalTable->rowCount(), 1, spinBoxIntervalEnd);
		intervalTable->setCellWidget(intervalTable->rowCount(), 2, btnAddInterval);
	}

	void FilterTimeline::setFilter(Filter::sptr filter) {
		if (!this->filter.isNull()) {
			this->filter->unsubscribe(this);
		}
		this->filter = filter;

		this->filter->subscribe(this);

		update();
	}

	void FilterTimeline::intervalRemoved(int id) {
		emit removeInterval(filter, id);
	}

	void FilterTimeline::intervalChanged(UIntegerInterval::sptr newInterval) {
		emit activateInterval(filter, newInterval);
	}

	void FilterTimeline::btnAddIntervalClicked() {
		UIntegerInterval::sptr newInterval(new UIntegerInterval(spinboxIntervalStart->value(), spinBoxIntervalEnd->value()));
		emit activateInterval(filter, newInterval);
	}
}  // namespace view