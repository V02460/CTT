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

    static const QString kParamMixRatioStr;

    /**
    * Creates a new MixFilter object with two modules to mix.
    *
    * @param module1 The first module which is mixed
    * @param module2 The second module which is mixed
    * @throws IllegalArgumentException if resolution of the two modules does not match
    */
    MixFilter(Module::sptr module1, Module::sptr module2);

    /**
     * MixFilter destructor.
     */
    virtual ~MixFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return "filter_mix"; };
	virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
	
    virtual ::model::saveable::Saveable::SaveableType getType() const Q_DECL_OVERRIDE;
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const ::model::Module &module) const Q_DECL_OVERRIDE;

private:
    ::model::Module::sptr module2;
};

}  // namespace filter
}  // namespace model

#endif  //_MIXFILTER_H
