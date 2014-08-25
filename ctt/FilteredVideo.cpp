#include "FilteredVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::IllegalStateException;
using ::model::saveable::Saveable;
using ::model::video::Video;

FilteredVideo::FilteredVideo(Video::sptr baseVideo) : baseVideo(baseVideo) {

}

FilteredVideo::FilteredVideo()
{
	isDummyFlag = true;
}

void FilteredVideo::addFilter(Filter::sptr filter, unsigned int pos) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to add a filter to a dummy FilteredVideo.");
	}


	QList<const Module*> usesList(getUsesList());

	foreach(const Module* module, usesList)
	{
		if (filter->uses(*module))
		{
			throw new IllegalArgumentException("Tried to add a filter to a FilteredVideo that is already used by the filtered video.");
		}
	}

	if (pos > (unsigned int) filters.count())
	{
		throw new IllegalArgumentException("Can not insert a Filter into a FilteredVideo with " + QString::number(filters.count())
			+ " Filters at position " + QString::number(pos) + ".");
	}

	if (pos < (unsigned int) filters.count())
	{
		filters.at(pos)->setPreviousModule(filter);
	}

	if (pos > 0)
	{
		filter->setPreviousModule(filters.at(pos - 1));
	}
	if (pos = 0)
	{
		filter->setPreviousModule(baseVideo);
	}

	filters.insert(pos, filter);
}

Filter::sptr FilteredVideo::removeFilter(unsigned int pos) {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to remove a filter from a dummy FilteredVideo.");
	}

	if (pos >= (unsigned int) filters.count())
	{
		throw new IllegalArgumentException("Can not remove a Filter from a FilteredVideo with " + QString::number(filters.count())
			+ " Filters from position " + QString::number(pos) + ".");
	}

	if (pos = 0)
	{
		filters[1]->setPreviousModule(baseVideo);
	}
	else if (pos < ((unsigned int) filters.count() - 1))
	{
		filters[pos + 1]->setPreviousModule(filters[pos - 1]);
	}

	Filter::sptr result(filters[pos]);

	filters.removeAt(pos);
	
	return result;
}

unsigned int FilteredVideo::getFilterCount() const {
    if (isDummy())
    {
		throw new IllegalStateException("Tried to request the filter count of a dummy FilteredVideo.");
	}

	return filters.count();
}

QList<Filter::sptr> FilteredVideo::getFilterList() const {
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request the filters of a dummy FilteredVideo.");
	}

	return filters;
}

model::frame::Frame::sptr FilteredVideo::getFrame(unsigned int frameNumber) const{
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request a frame of a dummy FilteredVideo.");
	}

	if (filters.empty())
	{
		return baseVideo->getFrame(frameNumber);
	}

	return filters.last()->getFrame(frameNumber);
}

Memento FilteredVideo::getMemento() const {
    throw new NotImplementedException();
}

void FilteredVideo::restore(Memento memento) {
    throw new NotImplementedException();
}

Saveable::sptr FilteredVideo::getDummy() {
	return Saveable::sptr(new FilteredVideo);
}

QList<const Module*> FilteredVideo::getUsesList() const
{
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request a list of used modules from a dummy FilteredVideo.");
	}

	QList<const Module*> result;
	result.append(this);
	result.append(baseVideo->getUsesList());
	for (int i = 0; i < filters.size(); ++i) {
		result.append(filters.at(i)->getUsesList());
	}

	return result;
}

unsigned int FilteredVideo::getFrameCount() const
{
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request the frame count of a dummy FilteredVideo.");
	}

	if (filters.isEmpty())
	{
		return baseVideo->getFrameCount();
	}
	else
	{
		return filters.last()->getFrameCount();
	}
}

bool FilteredVideo::uses(const model::Module &module) const
{
	if (isDummy())
	{
		throw new IllegalStateException("Tried to ask a dummy FilteredVideo whether it used a specific module.");
	}

	return getUsesList().contains(&module);
}

model::video::VideoMetadata FilteredVideo::getMetadata() const
{
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request metadata from a dummy FilteredVideo.");
	}

	if (filters.isEmpty())
	{
		return baseVideo->getMetadata();
	}
	else
	{
		VideoMetadata result(filters.last()->getResolution(), baseVideo->getMetadata().getFPS(), 
			filters.last()->getFrameCount(), baseVideo->getMetadata().getAdditionalMetadata());

		return result;
	}
}

Saveable::SaveableType FilteredVideo::getSaveableType() {
    return SaveableType::filteredVideo;
}

Video::sptr FilteredVideo::getBaseVideo() const {
	return baseVideo;
}

QSharedPointer<QOpenGLContext> FilteredVideo::getContext() const
{
	if (isDummy())
	{
		throw new IllegalStateException("Tried to request the context from a dummy FilteredVideo.");
	}

	return baseVideo->getContext();
}

}  // namespace filter
}  // namespace model