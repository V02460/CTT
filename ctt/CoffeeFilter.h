#ifndef _COFFEEFILTER_H
#define _COFFEEFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QCoreApplication>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 * Provides a version of the predecessors frame with coffee stains on it.
 */
class CoffeeFilter : public Filter  {
    Q_OBJECT

public:
    typedef QScopedPointer<CoffeeFilter> uptr;
    typedef QSharedPointer<CoffeeFilter> sptr;
    typedef QWeakPointer<CoffeeFilter> wptr;

    static const QByteArray kFilterID;

    /**
     * Creates a new CoffeeFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    CoffeeFilter(Module::sptr predecessor);
    virtual ~CoffeeFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return true; }
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
	virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
	
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    virtual bool uses(const Module &module) const Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType() { return Saveable::coffeeFilter; }
};

}  // namespace filter
}  // namespace model

#endif  //_COFFEEFILTER_H
