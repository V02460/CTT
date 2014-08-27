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
 * Provides a blurred version of the predecessors frame.
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
    virtual QString getName() const Q_DECL_OVERRIDE { return "filter_blur"; }
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const Module &module) const Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType() { return Saveable::blurFilter; }

private:
    static const QString kParamRadiusStr;
};

}  // namespace filter
}  // namespace model

#endif  //_BLURFILTER_H
