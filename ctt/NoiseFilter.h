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

	NoiseFilter(const Module &predecessor);
	virtual ~NoiseFilter();

	virtual bool supportsIntervals() const;
	virtual QString getName() const;
	virtual frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_NOISEFILTER_H
