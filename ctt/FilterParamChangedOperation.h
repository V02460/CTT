#ifndef _FILTERPARAMCHANGEDOPERATION_H
#define _FILTERPARAMCHANGEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "FilterListOperation.h"
#include "FilterParam.h"
#include "FilteredVideo.h"
#include "Filter.h"

namespace controller {
namespace operation {

/**
 * The FilterParamChangedOperation is providing functionality for doing and undoing changing a Filter's parameters.
 */
class FilterParamChangedOperation : public FilterListOperation {
public:
    typedef QScopedPointer<FilterParamChangedOperation> uptr;
    typedef QSharedPointer<FilterParamChangedOperation> sptr;
    typedef QWeakPointer<FilterParamChangedOperation> wptr;

    /**
     * Constructs an Operation that is responsible for changing a filterparameter, using the new filterparameter and a
     * pointer to the Filter it applies to.
     *
     * @param newParam The new parameter which should be applied to a Filter.
     * @param filter A pointer to the Filter which parameter should be changed.
     */
    FilterParamChangedOperation(::model::filter::FilterParam::sptr newParam, ::model::filter::Filter::sptr filter);

    /**
     * Manages requests to change a filter's parameter.
     */
    void doOperation();

    /**
     * Manages requests undo changing a filter's parameter.
     */
    void undoOperation();
private:
    ::model::filter::Filter::sptr filter;

    /**
     * The new parameter that should replace the filter's old parameter.
     */
    ::model::filter::FilterParam::sptr newParam;

    /**
     * The old parameter that is replaced by the filter's new parameter.
     */
    ::model::filter::FilterParam::sptr oldParam;
};

}  // namespace operation
}  // namespace controller

#endif  //_FILTERPARAMCHANGEDOPERATION_H
