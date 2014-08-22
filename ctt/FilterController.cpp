#include "FilterController.h"

namespace controller {

using ::model::filter::Filter;
using ::model::filter::FilterParam;
using ::model::filter::FilteredVideo;
using ::controller::operation::FilterParamChangedOperation;
using ::controller::operation::FilterRemovedOperation;
using ::controller::operation::FilterMovedOperation;
using ::controller::operation::OperationList;
using ::controller::operation::Operation;
using ::controller::operation::FilterAddedOperation;
using ::model::filter::FilterFactory;

FilterController::FilterController(FilteredVideo::sptr video) : video(video), list(OperationList::getInstance()) {}

void FilterController::insertFilter(QString id) {
	list->doOperation(QSharedPointer<Operation>(new FilterAddedOperation(FilterFactory::createFilter(id), video)));
}

void FilterController::moveFilter(int oldPos, int newPos) {
	list->doOperation(QSharedPointer<Operation>(new FilterMovedOperation(oldPos, newPos, video)));
}

void FilterController::changeFilterParam(const Filter::sptr filter, FilterParam::sptr param) {
	list->doOperation(QSharedPointer<Operation>(new FilterParamChangedOperation(param, filter)));
}

void FilterController::removeFilter(int pos) {
	list->doOperation(QSharedPointer<Operation>(new FilterRemovedOperation(pos, video)));
}

void FilterController::setVideo(FilteredVideo::sptr newVideo) {
	video = newVideo;
}

}  // namespace controller