#ifndef _RESCALEFILTER_H
#define _RESCALEFILTER_H

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
* Provides a new version of the predecessors frame which has been rescaled.
*/
class RescaleFilter : public Filter {
    Q_OBJECT

public:
    typedef QScopedPointer<RescaleFilter> uptr;
    typedef QSharedPointer<RescaleFilter> sptr;
    typedef QWeakPointer<RescaleFilter> wptr;

    static const QByteArray kFilterID;

    static const QByteArray kParamNewSizeWidth;
    static const QByteArray kParamNewSizeHeight;

    /**
     * Creates a new RescaleFilter object with a given previous module.
     *
     * @param predecessor The previous module of this filter.
     */
    explicit RescaleFilter(Module::sptr predecessor);

    /**
     * Destroys the RescaleFilter.
     */
    virtual ~RescaleFilter();

    virtual bool supportsIntervals() const Q_DECL_OVERRIDE { return false; }
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
	
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType() { return Saveable::rescaleFilter; }
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
	RescaleFilter();
};

}  // namespace filter
}  // namespace model

#endif  //_RESCALEFILTER_H
