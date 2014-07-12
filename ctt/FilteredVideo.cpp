#include "FilteredVideo.h"

namespace model {
namespace filter {

using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;

FilteredVideo::FilteredVideo(Video::sptr baseVideo) {

}

void FilteredVideo::addFilter(Filter::sptr filter, unsigned int pos) {

}

Filter::sptr FilteredVideo::removeFilter(unsigned int pos) {

}

unsigned int FilteredVideo::getFilterCount() const {

}

QList<Filter::sptr> FilteredVideo::getFilterList() const {

}

model::frame::Frame::sptr FilteredVideo::getFrame(unsigned int frameNumber) const{

}

Memento FilteredVideo::getMemento() const {

}

void FilteredVideo::restore(Memento memento) {

}

Saveable::sptr FilteredVideo::getDummy() {

}

}  // namespace filter
}  // namespace model