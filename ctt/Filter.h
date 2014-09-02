#ifndef _FILTER_H
#define _FILTER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMap>    

#include "Module.h"
#include "Frame.h"
#include "Memento.h"
#include "FilterParam.h"
#include "UIntegerInterval.h"        
#include "FilterIntervalList.h"    

#include "AccessToDummyException.h"

namespace model {
namespace filter {

/**
 * An object which can attach itself to another module and outputs modified versions of the frames of this module.
 *
 */
class Filter : public ::model::Module, public QObject {
public:
    typedef QScopedPointer<Filter> uptr;
    typedef QSharedPointer<Filter> sptr;
    typedef QWeakPointer<Filter> wptr;

    /**
     * Constructs a Filter which works on predecessor. 
     *
     * @param predecessor The Module Filter is receiving its Frames from.
     */
    explicit Filter(Module::sptr predecessor);

    /**
     * Filter destructor.
     */
    virtual ~Filter();

    /**
     * Checks whether it is possible to use this Filter not on its previous module as a whole, but only on frames in
     * specific intervals.
     *
     * @return bool true only if the Filter supports being active only in specific intervals.
     * @throws AccessToDummyException if the the method was called on a dummy
     */
    virtual bool supportsIntervals() const = 0;

    /**
     * Returns a list of the different parameters of the filter with their names and values.
     *
     * @return QList<FilterParam> a list of the different parameters of the filter
     * @throws AccessToDummyException if the the method was called on a dummy
     */
    QList<FilterParam::sptr> getParams() const;

    /**
     * Sets the submitted parameter.
     *
     * @param parameter this parameter will be set
     * @throws IllegalArgumentException if the Filter doesn't have a parameter with the name or type of the submitted
     *         parameter
     * @throws AccessToDummyException if the the method was called on a dummy
     */
    void setParam(FilterParam::sptr parameter);

    /**
     * Tells the Filter to use the frames of the submitted Module as source material for its own frames.
     *
     * @param predecessor the Filter will use the frames of this module as source material for its own frames
     * @throws IllegalArgumentException if predecessor is null
     * @throws AccessToDummyException if the the method was called on a dummy
     */
    void setPreviousModule(::model::Module::sptr predecessor);

    /**
     * Returns a designation of this type of Filter
     *
     * @return QString a designation of this type of Filter
     * @throws AccessToDummyException if the the method was called on a dummy
     */
    virtual QString getName() const = 0;

    /**
     * Activates the Filter in the submitted interval.
     *
     * @param interval the filter will be activated in this interval
     * @throws AccessToDummyException if the the method was called on a dummy or a Filter without interval support
     */
    void activate(UIntegerInterval::sptr interval);

    /**
     * Deactivates the Filter in the submitted interval.
     *
     * @param interval the filter will be deactivated in this interval
     * @throws AccessToDummyException if the the method was called on a dummy or a Filter without interval support
     */
    void deactivate(UIntegerInterval::sptr interval);

    /**
     * Returns a list of all the intervals the filter is active in.
     *
     * @return List<IntegerInterval> a list of all the intervals the filter is active in
     * @throws AccessToDummyException if the the method was called on a dummy or a Filter without interval support
     */
    QList<UIntegerInterval::sptr> getListOfActiveIntervals();

    virtual unsigned int getFrameCount() const Q_DECL_OVERRIDE;

    virtual QSize getResolution() const Q_DECL_OVERRIDE;

    virtual ::model::saveable::Memento getMemento() const Q_DECL_OVERRIDE;
    virtual void restore(::model::saveable::Memento memento) Q_DECL_OVERRIDE;
    static Saveable::SaveableType getSaveableType() { return Saveable::filter; }
    virtual QList<const Module*> getUsesList() const Q_DECL_OVERRIDE;

protected:

    template <class T>
    void newParameter(QString name, T initValue) {
        if (isDummy()) {
            throw ::exception::AccessToDummyException();
        }
		parameters.insert(name, FilterParam::sptr(new FilterParam(name, initValue)));
    }

    template <class T>
    T getParamValue(QString key, T defaultValue = T()) const {
        if (isDummy()) {
            throw ::exception::AccessToDummyException();
        }
        FilterParam::sptr param = parameters.value(key, FilterParam::sptr(new FilterParam(key, defaultValue)));
        return param->getValue().value<T>();
    }

    Module *getPredecessor() const;

	Filter() {}

private:
    Q_DISABLE_COPY(Filter)

    ::model::FilterIntervalList::sptr intervals; /**< The Intervals in which the Filter is active */
    QMap<QString, FilterParam::sptr> parameters; /**< Parameters modifying the filters behavior */
    Module::sptr predecessor; /**< The Filter gets the frames it modifies from this module */
};

}  // namespace filter
}  // namespace model

#endif  //_FILTER_H
