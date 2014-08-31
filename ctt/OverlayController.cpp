#include "OverlayController.h"
#include "FilteredVideo.h"
#include "Module.h"
#include "Operation.h"
#include "OperationList.h"
#include "FilterAddedOperation.h"
#include "FilterRemovedOperation.h"
#include "FilterMovedOperation.h"
#include "FilterFactory.h"


namespace controller {

	using ::model::filter::FilteredVideo;
	using ::model::Module;
	using ::controller::operation::Operation;
	using ::controller::operation::OperationList;
	using ::controller::operation::FilterAddedOperation;
	using ::controller::operation::FilterRemovedOperation;
	using ::controller::operation::FilterMovedOperation;
	using ::model::filter::FilterFactory;

	OverlayController::OverlayController(FilteredVideo::sptr video) : currentVideo(video){

	}

	void OverlayController::insertOverlay(QString id) {
		Module::sptr module;
		if (currentVideo->getFilterCount() == 0) {
			module = currentVideo->getBaseVideo();
		}
		else {
			module = currentVideo->getFilterList().back();
		}
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new FilterAddedOperation(FilterFactory::createFilter(id, module), currentVideo)));
	}

	void OverlayController::moveOverlay(int oldPos, int newPos) {
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new FilterMovedOperation(oldPos, newPos, currentVideo)));
	}

	void OverlayController::removeOverlay(int pos) {
		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new FilterRemovedOperation(pos, currentVideo)));
	}

}  // namespace controller