#include "FilteredVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

FilteredVideo::FilteredVideo(Video::sptr baseVideo) {
    throw new NotImplementedException();
}

void FilteredVideo::addFilter(Filter::sptr filter, unsigned int pos) {
    throw new NotImplementedException();
}

Filter::sptr FilteredVideo::removeFilter(unsigned int pos) {
    throw new NotImplementedException();
}

unsigned int FilteredVideo::getFilterCount() const {
    throw new NotImplementedException();
}

QList<Filter::sptr> FilteredVideo::getFilterList() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr FilteredVideo::getFrame(unsigned int frameNumber) const{
    throw new NotImplementedException();
}

Memento FilteredVideo::getMemento() const {
    throw new NotImplementedException();
}

void FilteredVideo::restore(Memento memento) {
    throw new NotImplementedException();
}

Saveable::sptr FilteredVideo::getDummy() {
    throw new NotImplementedException();
}

Saveable::SaveableType FilteredVideo::getType() const {
	return Saveable::SaveableType::filteredVideo;
}

}  // namespace filter
}  // namespace model