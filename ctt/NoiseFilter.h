#ifndef _NOISEFILTER_H
#define _NOISEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 * Provides a new version of the predecessors frame where noise has been added.
 */
class NoiseFilter : public Filter {
public:
    typedef QScopedPointer<NoiseFilter> uptr;
    typedef QSharedPointer<NoiseFilter> sptr;
    typedef QWeakPointer<NoiseFilter> wptr;

    /**
     * Creates a new NoiseFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit NoiseFilter(Module::sptr predecessor);
  
    /**
     * Destroys the NoiseFilter.
     */
    virtual ~NoiseFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const;
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
    static Saveable::SaveableType getSaveableType();
};

}  // namespace filter
}  // namespace model

#endif  //_NOISEFILTER_H
