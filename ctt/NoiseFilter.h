#ifndef _NOISEFILTER_H
#define _NOISEFILTER_H

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
 * Provides a new version of the predecessors frame where noise has been added.
 */
class NoiseFilter : public Filter {
    Q_OBJECT

public:
    typedef QScopedPointer<NoiseFilter> uptr;
    typedef QSharedPointer<NoiseFilter> sptr;
    typedef QWeakPointer<NoiseFilter> wptr;

    static const QByteArray kFilterID;

    static const QString kParamIntensityStr;

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
    virtual QString getName() const Q_DECL_OVERRIDE { return QCoreApplication::translate("Filter", kFilterID); }
    virtual ::model::frame::Frame::sptr getFrame(unsigned int frameNumber) const Q_DECL_OVERRIDE;
	
    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;
	static Saveable::sptr getDummy();
    static ::model::saveable::Saveable::SaveableType getSaveableType() { return Saveable::noiseFilter; }

private:
	NoiseFilter();
};

}  // namespace filter
}  // namespace model

#endif  //_NOISEFILTER_H
