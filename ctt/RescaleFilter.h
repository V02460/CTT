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

/**
* Provides a new version of the predecessors frame which has been rescaled.
*/
class RescaleFilter : public Filter {
public:
    typedef QScopedPointer<RescaleFilter> uptr;
    typedef QSharedPointer<RescaleFilter> sptr;
    typedef QWeakPointer<RescaleFilter> wptr;

    /**
     * Creates a new RescaleFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit RescaleFilter(Module::sptr predecessor);

    /**
     * RescaleFilter destructor.
     */
    virtual ~RescaleFilter();

    virtual bool supportsIntervals() const;
    virtual QString getName() const;
    virtual ::model::frame::Frame getFrame(unsigned int frameNumber) const;
};

}  // namespace filter
}  // namespace model

#endif  //_RESCALEFILTER_H
