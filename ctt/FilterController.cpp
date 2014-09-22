#include "FilterController.h"

#include "NotImplementedException.h"

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
using ::model::Module;

using ::exception::NotImplementedException;

FilterController::FilterController(FilteredVideo::sptr video) : video(video) {}

void FilterController::insertFilter(QString id) {
	Module::sptr module;
	if (video->getFilterCount() == 0) {
		module = video->getBaseVideo();
	} else {
		module = video->getFilterList().back();
	}
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new FilterAddedOperation(FilterFactory::createFilter(id, module), video)));
}

void FilterController::moveFilter(int oldPos, int newPos) {
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new FilterMovedOperation(oldPos, newPos, video)));
}

void FilterController::changeFilterParam(const Filter::sptr filter, FilterParam::sptr param) {
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new FilterParamChangedOperation(param, filter)));
}

void FilterController::removeFilter(int pos) {
	OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
		new FilterRemovedOperation(pos, video)));
}

void FilterController::setVideo(FilteredVideo::sptr newVideo) {
	video = newVideo;
}

void FilterController::update() {
	throw NotImplementedException();
}

}  // namespace controller