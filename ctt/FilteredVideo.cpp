#include "FilteredVideo.h"
#include "Video.h"
#include "Filter.h"
#include "FilterList.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace video {

FilteredVideo::FilteredVideo(Video baseVideo) {

}

void FilteredVideo::addFilter(Filter filter, unsigned int pos) {

}

Filter FilteredVideo::removeFilter(unsigned int pos) {

}

unsigned int FilteredVideo::getFilterCount() {

}

FilterList FilteredVideo::getFilterList() {

}

VideoMetadata FilteredVideo::getMetadata() {

}

Frame FilteredVideo::getFrame(unsigned int frameNumber) {

}

Memento FilteredVideo::getMemento() {

}

void FilteredVideo::restore(Memento memento) {

}

Saveable* FilteredVideo::getDummy() {

}

}  // namespace video
}  // namespace model