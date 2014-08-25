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
    virtual QString getName() const Q_DECL_OVERRIDE { return "filter_noise"; }
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
	
    virtual ::model::saveable::Saveable::SaveableType getType() const Q_DECL_OVERRIDE { return Saveable::noiseFilter; };
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const ::model::Module &module) const Q_DECL_OVERRIDE;
};

}  // namespace filter
}  // namespace model

#endif  //_NOISEFILTER_H
