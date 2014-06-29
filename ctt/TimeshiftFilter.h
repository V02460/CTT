#if !defined(_TIMESHIFTFILTER_H)
#define _TIMESHIFTFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace filter {

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class TimeshiftFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_TIMESHIFTFILTER_H
