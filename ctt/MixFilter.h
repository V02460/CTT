#ifndef _MIXFILTER_H
#define _MIXFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"
#include "Surface.h"

namespace model {
namespace filter {

/**
 * Provides a new version of the predecessors frame which has been mixed with another texture.
 */
class MixFilter : public Filter {
public:
    typedef QScopedPointer<MixFilter> uptr;
    typedef QSharedPointer<MixFilter> sptr;
    typedef QWeakPointer<MixFilter> wptr;

    /**
    * Creates a new MixFilter object with a given previous module and a Surface which provides the texture to be
    * mixed with a frame.
    *
    * @param predecessor The previous module of this filter.
    * @param surface The surface which provides the texture to be mixed with a frame.
    */
    MixFilter(Module::sptr predecessor, Module::sptr module);

    /**
     * MixFilter destructor.
     */
    virtual ~MixFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const Q_DECL_OVERRIDE;
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    virtual ::model::saveable::Saveable::SaveableType getType() const Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const Module &module) const Q_DECL_OVERRIDE;
};

}  // namespace filter
}  // namespace model

#endif  //_MIXFILTER_H
