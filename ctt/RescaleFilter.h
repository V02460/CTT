#if !defined(_RESCALEFILTER_H)
#define _RESCALEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class RescaleFilter : public Filter {
public:
	typedef QScopedPointer<RescaleFilter> uptr;
	typedef QSharedPointer<RescaleFilter> sptr;
	typedef QWeakPointer<RescaleFilter> wptr;

	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_RESCALEFILTER_H
