#ifndef _FILTEREDVIDEO_H
#define _FILTEREDVIDEO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Video.h"
#include "Observable.h"
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

/**
 * Represents a Video with a filter pipeline modifying its frames.
 *
 */
class FilteredVideo : public ::model::video::Video, public ::model::Observable {
public:
    typedef QScopedPointer<FilteredVideo> uptr;
    typedef QSharedPointer<FilteredVideo> sptr;
    typedef QWeakPointer<FilteredVideo> wptr;

    /**
     * Creates a new FilteredVideo with an initially empty FilterList, using the submitted Video as base video. The base
     * video provides the frames which will be modified by the filter pipeline.
     *
     * @param baseVideo this Video will be used as base video
     */
    explicit FilteredVideo(::model::video::Video::sptr baseVideo);

    /**
     * Ads the submitted Filter to the filter pipeline at the submitted position.
     *
     * @param filter this filter will be added to the pipeline
     * @param pos the new filter will be added at this position
     * @throws IllegalArgumentException if the submitted position is too great
     */
    void addFilter(Filter::sptr filter, unsigned int pos);

    /**
     * Removes the Filter at the submitted Position
     *
     * @param pos the position of the Filter to be removed
     * @return model::filter::Filter::sptr the Filter which has been removed
     * @throws IllegalArgumentException if there is no Filter at the submitted position
     */
    ::model::filter::Filter::sptr removeFilter(unsigned int pos);

    /**
     * Returns the number of Filters this FilteredVideo has in its filter pipeline.
     *
     * @return unsigned int the number of Filters this FilteredVideo has in its filter pipeline
     */
    unsigned int getFilterCount() const;

    /**
     * Returns a QList containing all the Filters this FilteredVideo uses in its filter pipeline in the right order.
     *
     * @return QList<model::filter::Filter> a QList containing all the Filters this FilteredVideo uses in its filter
     *     pipeline in the right order
     */
    QList<::model::filter::Filter::sptr> getFilterList() const;

	/**
	 * Returns the base video.
	 *
	 * @return The base video.
	 */
	::model::video::Video::sptr getBaseVideo() const;

    virtual model::frame::Frame::sptr getFrame(unsigned int frameNumber) const;
	virtual QList<const Module*> getUsesList() const;
	virtual unsigned int getFrameCount() const;
	virtual bool uses(const model::Module &module) const;
	virtual model::video::VideoMetadata getMetadata() const;
	virtual QSharedPointer<QOpenGLContext> getContext() const;

    virtual ::model::saveable::Memento getMemento() const;
    virtual void restore(::model::saveable::Memento memento);
	static Saveable::sptr getDummy();
    static Saveable::SaveableType getSaveableType();

private:
    /**
     * Creates a dummy FilteredVideo.
     */
    FilteredVideo();

    ::model::video::Video::sptr baseVideo; /**< This provides the frames which will be modified by the filter pipeline. */
    QList<::model::filter::Filter::sptr> filters; /**< The filter pipeline */
};

}  // namespace filter
}  // namespace model

#endif  //_FILTEREDVIDEO_H
