#include "FilterRemovedOperation.h"

namespace controller {
namespace operation {

using ::model::filter::FilteredVideo;

FilterRemovedOperation::FilterRemovedOperation(int index, FilteredVideo::sptr filteredVideo)
: index(index), filteredVideo(filteredVideo), memento(filteredVideo->getMemento()) {}

void FilterRemovedOperation::doOperation() {
	filteredVideo->removeFilter(index);
}

void FilterRemovedOperation::undoOperation() {
	filteredVideo->restore(memento);
	filteredVideo->changed();
}

}  // namespace operation
}  // namespace controller