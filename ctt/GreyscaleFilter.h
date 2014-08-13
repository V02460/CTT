#ifndef _GREYSCALEFILTER_H
#define _GREYSCALEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 * Provides a greyscale version of the predecessors frame.
 */
class GreyscaleFilter : public Filter {
public:
    typedef QScopedPointer<GreyscaleFilter> uptr;
    typedef QSharedPointer<GreyscaleFilter> sptr;
    typedef QWeakPointer<GreyscaleFilter> wptr;

    /**
     * Creates a new GreyscaleFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit GreyscaleFilter(Module::sptr predecessor);

    /**
     * GreyscaleFilter destructor.
     */
    virtual ~GreyscaleFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const;
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
	virtual ::model::saveable::Saveable::SaveableType getType() const;
};

}  // namespace filter
}  // namespace model

#endif  //_GREYSCALEFILTER_H
