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
    virtual QString getName() const Q_DECL_OVERRIDE { return "filter_greyscale"; }
    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const ::model::Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const ::model::Module &module) const Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType();
};

}  // namespace filter
}  // namespace model

#endif  //_GREYSCALEFILTER_H
