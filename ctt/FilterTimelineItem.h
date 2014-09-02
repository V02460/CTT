#ifndef _FILTERTIMELINEITEM_H
#define _FILTERTIMELINEITEM_H

#include <QSpinBox>
#include <QPushButton>

#include "UIntegerInterval.h"

namespace view {
	class FilterTimelineItem : public QObject {
		Q_OBJECT
	public:
		typedef QScopedPointer<FilterTimelineItem> uptr;
		typedef QSharedPointer<FilterTimelineItem> sptr;
		typedef QWeakPointer<FilterTimelineItem> wptr;

		FilterTimelineItem(int id, ::model::UIntegerInterval::sptr interval, int maxLength);

		QSpinBox* getIntervalStartSpinBox();
		QSpinBox* getIntervalEndSpinBox();
		QPushButton* getRemoveIntervalButton();

	signals:
		void intervalChanged(::model::UIntegerInterval::sptr newInterval);
		void intervalRemoveClicked(int id);

	private slots:
		void intervalValueChanged(int value);
		void removeIntervalClicked(bool checked);
	private:
		int id;

		QSpinBox *intervalStart;
		QSpinBox *intervalEnd;
		QPushButton *removeInterval;
	};
}
#endif