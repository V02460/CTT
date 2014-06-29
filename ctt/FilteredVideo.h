


#if !defined(_FILTEREDVIDEO_H)
#define _FILTEREDVIDEO_H

#include "Video.h"
#include "Observable.h"
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

/**
 * Represents a Video with a filter pipeline modifying its frames.
 *
 */
class FilteredVideo : public Video, public Observable {
public:

	/**
	 * Creates a new FilteredVideo with an initially empty FilterList, using the submitted Video as base video. The base video provides the frames which will be modified by the filter pipeline.
	 * @param baseVideo this Video will be used as base video
	 */
	FilteredVideo(Video baseVideo);

    /**
     * Ads the submitted Filter to the filter pipeline at the submitted position.
     *
     * @param filter this filter will be added to the pipeline
     * @param pos the new filter will be added at this position
	 * @throws IllegalArgumentException if the submitted position is too great
     */
    void addFilter(Filter filter, unsigned int pos);

    /**
     * Removes the Filter at the submitted Position
     *
     * @param pos the position of the Filter to be removed
     * @return Filter the Filter which has been removed
	 * @throws IllegalArgumentException if there is no Filter at the submitted position
     */
	Filter removeFilter(unsigned int pos);

    /**
     * Returns the number of Filters this FilteredVideo has in its filter pipeline.
     *
     * @return unsigned int the number of Filters this FilteredVideo has in its filter pipeline
     */
    unsigned int getFilterCount();

    /**
     * Returns a QList containing all the Filters this FilteredVideo uses in its filter pipeline in the right order.
     *
     * @return QList<Filter> a QList containing all the Filters this FilteredVideo uses in its filter pipeline in the right order
     */
    QList<Filter> getFilterList();

    VideoMetadata getMetadata();

	Frame getFrame(unsigned int frameNumber);
	
	Memento getMemento();

    void restore(Memento memento);

    Saveable* getDummy();
private:
	/**
	 * Creates a dummy FilteredVideo.
	 */
	FilteredVideo();

    Video *baseVideo; /**< This provides the frames which will be modified by the filter pipeline. */
    QList<Filter> *filters; /**< The filter pipeline */
};

#endif  //_FILTEREDVIDEO_H
