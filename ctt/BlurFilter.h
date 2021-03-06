#ifndef _BLURFILTER_H
#define _BLURFILTER_H

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
 * Provides a blurred version of the predecessors frame.
 */
class BlurFilter : public Filter {
    Q_OBJECT

public:
    typedef QScopedPointer<BlurFilter> uptr;
    typedef QSharedPointer<BlurFilter> sptr;
    typedef QWeakPointer<BlurFilter> wptr;

    static const QByteArray kFilterID;
    static const QByteArray kParamRadiusStr;

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
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
    
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
	static Saveable::SaveableType getSaveableType() { return Saveable::blurFilter; }
	virtual SaveableType saveableType() const Q_DECL_OVERRIDE { return getSaveableType(); }

private:
    /**
     * Creates a dummy BlurFilter.
     */
	BlurFilter();
};

}  // namespace filter
}  // namespace model

#endif  //_BLURFILTER_H
