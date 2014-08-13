#ifndef _BLURFILTER_H
#define _BLURFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"
#include "Saveable.h"

namespace model {
namespace filter {

/**
 * Provides a blured version of the predecessors frame.
 */
class BlurFilter : public Filter {
public:
    typedef QScopedPointer<BlurFilter> uptr;
    typedef QSharedPointer<BlurFilter> sptr;
    typedef QWeakPointer<BlurFilter> wptr;

    /**
     * Creates a new BlurFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit BlurFilter(Module::sptr predecessor);

    /**
     * BlurFilter destructor.
     */
    virtual ~BlurFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const;
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
	virtual ::model::saveable::Saveable::SaveableType getType() const;
};

}  // namespace filter
}  // namespace model

#endif  //_BLURFILTER_H
