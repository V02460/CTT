#include "FilterMovedOperation.h"

namespace controller {
namespace operation {

using ::model::filter::Filter;
using ::model::filter::FilterParam;

FilterMovedOperation::FilterMovedOperation(int oldPos, int newPos, model::filter::FilteredVideo::sptr filteredVideo)
	: oldPos(oldPos), newPos(newPos), filteredVideo(filteredVideo), memento(filteredVideo->getMemento()) {

	if (oldPos < newPos) {
		newPos--;
	}
}

void FilterMovedOperation::doOperation() {
	Filter::sptr filter = filteredVideo->removeFilter(oldPos);
	filteredVideo->addFilter(filter, newPos);
}

void FilterMovedOperation::undoOperation() {
	filteredVideo->restore(memento);
}

}  // namespace operation
}  // namespace controller