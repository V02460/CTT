#include "FilteredVideo.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::video::VideoMetadata;
using ::model::frame::Frame;
using ::model::saveable::Memento;
using ::model::saveable::Saveable;
using ::exception::NotImplementedException;
using ::exception::AccessToDummyException;
using ::model::saveable::Saveable;
using ::model::video::Video;

const QString FilteredVideo::baseVideoStringId = "baseVideo";
const QString FilteredVideo::filtersStringId = "filters";
const QString FilteredVideo::numberOfFiltersStringId = "numberOfFilters";

FilteredVideo::FilteredVideo(Video::sptr baseVideo) : baseVideo(baseVideo) {
	baseVideo->subscribe(this);
}

FilteredVideo::FilteredVideo() {
	isDummyFlag = true;
}

void FilteredVideo::addFilter(Filter::sptr filter, unsigned int pos) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	QList<const Module*> usesList(getUsesList());

	for each(const Module* module in usesList)
	{
		if (filter->uses(*module))
		{
			throw IllegalArgumentException("Tried to add a filter to a FilteredVideo using modules already used by the filtered video.");
		}
	}

	if (pos > static_cast<unsigned int>(filters.count()))
	{
		throw IllegalArgumentException("Can not insert a Filter into a FilteredVideo with " + QString::number(filters.count())
			+ " Filters at position " + QString::number(pos) + ".");
	}

	if (pos < static_cast<unsigned int>(filters.count()))
	{
		filters.at(pos)->setPreviousModule(filter);
	}

	if (pos > 0)
	{
		filter->setPreviousModule(filters.at(pos - 1));
	}
	if (pos == 0)
	{
		filter->setPreviousModule(baseVideo);
	}

	filters.insert(pos, filter);

	filter->subscribe(this);
	changed();
}

Filter::sptr FilteredVideo::removeFilter(unsigned int pos) {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (pos >= static_cast<unsigned int>(filters.count()))
	{
		throw IllegalArgumentException("Can not remove a Filter from a FilteredVideo with " + QString::number(filters.count())
			+ " Filters from position " + QString::number(pos) + ".");
	}

	if ((pos == 0) && (filters.size() >= 2))
	{
		filters[1]->setPreviousModule(baseVideo);
	}
	else if (pos < static_cast<unsigned int>(filters.count() - 1))
	{
		filters[pos + 1]->setPreviousModule(filters[pos - 1]);
	}

	Filter::sptr result(filters[pos]);
	result->unsubscribe(this);
	filters.removeAt(pos);
	
	changed();
	return result;
}

unsigned int FilteredVideo::getFilterCount() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return filters.count();
}

QList<Filter::sptr> FilteredVideo::getFilterList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return filters;
}

model::frame::Frame::sptr FilteredVideo::getFrame(unsigned int frameNumber) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	if (filters.empty())
	{
		return baseVideo->getFrame(frameNumber);
	}

	return filters.last()->getFrame(frameNumber);
}

Memento FilteredVideo::getMemento() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	Memento memento;

	memento.setSharedPointer(baseVideoStringId, baseVideo);

	memento.setUInt(numberOfFiltersStringId, filters.size());
	for (unsigned int i = 0; i < static_cast<unsigned int>(filters.size()); i++)
	{
		memento.setSharedPointer(filtersStringId + QString::number(i), filters[i]);
	}

	return memento;
}

void FilteredVideo::restore(Memento memento) {
	baseVideo = memento.getSharedPointer(baseVideoStringId).dynamicCast<Video>();
	
	filters.clear();

	for (unsigned int i = 0; i < memento.getUInt(numberOfFiltersStringId); i++)
	{
		filters.append(memento.getSharedPointer(filtersStringId + QString::number(i)).dynamicCast<Filter>());
		filters[i]->subscribe(this);
	}

	isDummyFlag = false;
}

Saveable::sptr FilteredVideo::getDummy() {
	return Saveable::sptr(new FilteredVideo);
}

QList<const Module*> FilteredVideo::getUsesList() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	QList<const Module*> result;
	result.append(this);
	result.append(baseVideo->getUsesList());
	for (int i = 0; i < filters.size(); ++i) {
		result.append(filters.at(i)->getUsesList());
	}
//	result.append(filters.last()->getUsesList());
	return result;
}

unsigned int FilteredVideo::getFrameCount() const {
	if (isDummy()) {
		throw AccessToDummyException();
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

model::video::VideoMetadata FilteredVideo::getMetadata() const {
	if (isDummy()) {
		throw AccessToDummyException();
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
    return Saveable::filteredVideo;
}

Video::sptr FilteredVideo::getBaseVideo() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return baseVideo;
}

QSharedPointer<QOpenGLContext> FilteredVideo::getContext() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
	return baseVideo->getContext();
}

void FilteredVideo::update()
{
	if (isDummy()) {
		throw AccessToDummyException();
	}
	changed();
}

FilteredVideo::~FilteredVideo()
{
    if (isDummy()) {
        return;
    }

	baseVideo->unsubscribe(this);
	for each (Filter::sptr filter in filters) {
		filter->unsubscribe(this);
	}
}

}  // namespace filter
}  // namespace model