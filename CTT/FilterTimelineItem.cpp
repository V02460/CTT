#include "FilterTimelineItem.h"

using ::model::UIntegerInterval;

namespace view {
	FilterTimelineItem::FilterTimelineItem(int id, UIntegerInterval::sptr interval, int maxLength) : id(id), intervalStart() ,intervalEnd(), removeInterval() {
		intervalStart->setMinimum(0);
		intervalStart->setMaximum(maxLength);
		intervalStart->setValue(interval->getStart());
		QObject::connect(intervalStart, SIGNAL(valueChanged(int)), this, SLOT(intervalValueChanged(int)));

		intervalEnd->setMinimum(0);
		intervalEnd->setMaximum(maxLength);
		intervalEnd->setValue(interval->getEnd());
		QObject::connect(intervalEnd, SIGNAL(valueChanged(int)), this, SLOT(intervalValueChanged(int)));

		removeInterval->setText(tr("REMOVE_INTERVAL"));
		QObject::connect(removeInterval, SIGNAL(clicked(bool)), this, SLOT(removeIntervalClicked(bool)));
	}

	QSpinBox* FilterTimelineItem::getIntervalStartSpinBox() {
		return intervalStart;
	}

	QSpinBox* FilterTimelineItem::getIntervalEndSpinBox() {
		return intervalEnd;
	}

	QPushButton* FilterTimelineItem::getRemoveIntervalButton() {
		return removeInterval;
	}

	void FilterTimelineItem::intervalValueChanged(int value) {
		UIntegerInterval::sptr newInterval(new UIntegerInterval(intervalStart->value(), intervalEnd->value()));

		emit intervalChanged(newInterval);
	}

	void FilterTimelineItem::removeIntervalClicked(bool checked) {
		emit intervalRemoveClicked(id);
	}
}