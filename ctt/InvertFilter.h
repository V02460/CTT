#ifndef _INVERTFILTER_H
#define _INVERTFILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QCoreApplication>

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"
#include "Saveable.h"

namespace model {
namespace filter {

/**
* Provides a inverted version of the predecessors frame.
*/
class InvertFilter : public Filter {
    Q_OBJECT

public:
    typedef QScopedPointer<InvertFilter> uptr;
    typedef QSharedPointer<InvertFilter> sptr;
    typedef QWeakPointer<InvertFilter> wptr;

    static const QByteArray kFilterID;

    /**
     * Creates a new InvertFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit InvertFilter(Module::sptr predecessor);

    /**
     * InvertFilter destructor.
     */
    virtual ~InvertFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE{return true;}
    virtual QString getName() const Q_DECL_OVERRIDE{return QCoreApplication::translate("Filter", kFilterID);}
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
    static ::model::saveable::Saveable::sptr getDummy();
    static ::model::saveable::Saveable::SaveableType getSaveableType() { return Saveable::invertFilter; }
    virtual ::model::saveable::Saveable::SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
    /**
     * Creates a dummy InvertFilter.
     */
    InvertFilter();
};

}  // namespace filter
}  // namespace model

#endif  //_INVERTFILTER_H
