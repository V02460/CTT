#if !defined(_NOISEFILTER_H)
#define _NOISEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

class NoiseFilter : public Filter {
public:
	typedef QScopedPointer<NoiseFilter> uptr;
	typedef QSharedPointer<NoiseFilter> sptr;
	typedef QWeakPointer<NoiseFilter> wptr;

	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

}  // namespace filter
}  // namespace model

#endif  //_NOISEFILTER_H
