#include "OverlayController.h"
#include "FilteredVideo.h"
#include "Module.h"
#include "Operation.h"
#include "OperationList.h"
#include "FilterAddedOperation.h"
#include "FilterRemovedOperation.h"
#include "FilterMovedOperation.h"
#include "FilterFactory.h"
#include "DifferenceFactory.h"
#include "PixelDiff.h"


namespace controller {

	using ::model::filter::FilteredVideo;
	using ::model::Module;
	using ::controller::operation::Operation;
	using ::controller::operation::OperationList;
	using ::controller::operation::FilterAddedOperation;
	using ::controller::operation::FilterRemovedOperation;
	using ::controller::operation::FilterMovedOperation;
	using ::model::filter::FilterFactory;
	using ::model::difference::DifferenceFactory;
	using ::model::difference::PixelDiff;

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

	void OverlayController::insertOverlayWithPixelDiff(QString id, FilteredVideo::sptr video1, FilteredVideo::sptr video2) {
		Module::sptr module;
		if (currentVideo->getFilterCount() == 0) {
			module = currentVideo->getBaseVideo();
		}
		else {
			module = currentVideo->getFilterList().back();
		}

		PixelDiff::sptr diff = DifferenceFactory::createPixelDiff(id, video1, video2);

		OperationList::getInstance()->doOperation(QSharedPointer<Operation>(
			new FilterAddedOperation(FilterFactory::createFilter(id, module, diff), currentVideo)));
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