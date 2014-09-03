#include "FilterAddedOperation.h"

namespace controller {
namespace operation {

using ::model::filter::Filter;
using ::model::filter::FilteredVideo;

FilterAddedOperation::FilterAddedOperation(Filter::sptr filter, FilteredVideo::sptr filteredVideo)
	: filter(filter), filteredVideo(filteredVideo), memento(filteredVideo->getMemento()) {}

void FilterAddedOperation::doOperation() {
	filteredVideo->addFilter(filter, filteredVideo->getFilterCount());
}

void FilterAddedOperation::undoOperation() {
	filteredVideo->restore(memento);
	filteredVideo->changed();
}

}  // namespace operation
}  // namespace controller