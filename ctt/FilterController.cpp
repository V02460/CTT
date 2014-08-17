#include "FilterController.h"

#include "NotImplementedException.h"

namespace controller {

using ::model::filter::Filter;
using ::model::filter::FilterParam;
using ::model::filter::FilteredVideo;
using ::exception::NotImplementedException;
using ::controller::operation::FilterParamChangedOperation;
using ::controller::operation::FilterRemovedOperation;
using ::controller::operation::FilterMovedOperation;

FilterController::FilterController(FilteredVideo::sptr video) : video(video) {}

void FilterController::insertFilter(QString id) {
	// TODO what is id referring to?
	throw new NotImplementedException();
}

void FilterController::moveFilter(int oldPos, int newPos) {
	// TODO operation needed
	FilterMovedOperation(oldPos, newPos, video);
}

void FilterController::changeFilterParam(const Filter::sptr filter, FilterParam::sptr param) {
	// TODO push to list
	FilterParamChangedOperation(param, filter);
}

void FilterController::removeFilter(int pos) {
	// TODO push to list
	FilterRemovedOperation(pos, video);
}

}  // namespace controller