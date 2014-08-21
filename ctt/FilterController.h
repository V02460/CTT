#ifndef _FILTERCONTROLLER_H
#define _FILTERCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>

#include "Observer.h"
#include "Filter.h"
#include "FilterParam.h"
#include "FilteredVideo.h"
#include "FilterParamChangedOperation.h"
#include "FilterRemovedOperation.h"
#include "FilterMovedOperation.h"
#include "OperationList.h"
#include "FilterAddedOperation.h"
#include "FilterFactory.h"

namespace controller {

/**
 * The FilterController receives notifications of changes in the video's filters and passes this information to all
 * relevant components.
 */
class FilterController : public QObject, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<FilterController> uptr;
    typedef QSharedPointer<FilterController> sptr;
    typedef QWeakPointer<FilterController> wptr;

    /**
     * Creates the FilterController with the Video it will observe filter changes over.
     *
     * @param video The observed video
     */
    FilterController(::model::filter::FilteredVideo::sptr video);

    /**
     * Initiates inserting a filter to the video's list of filters 
     * Is called when it receives a notification that a filter should be inserted.
     * Does nothing if id is not valid.
     *
     * @param id The ID of the filter that is to be added.
     */
    void insertFilter(QString id);

    /**
     * Initiates moving a filter to a specified position in the video's list of filters.
     * Is called when it receives a notification that a filter should be moved.
     * Moves Filter to the end if newPos is out of bounds.
     *
     * @param oldPos The position of the filter that is to be moved.
     * @param newPos The position the filter is to be moved to.
     */
    void moveFilter(int oldPos, int newPos);

    /**
     * Initiates changing a filter's parameters.
     * Is called when it receives a notification that a filter parameter should be changed.
     *
     * @param filter The Filter of which a parameter is to be changed.
     * @param param The parameter which is to be changed.
     */
    void changeFilterParam(const ::model::filter::Filter::sptr filter, ::model::filter::FilterParam::sptr param);

    /**
     * Initiates removing a filter from a video's list of filters.
     * Is called when it receives a notification that a filter should be removed.
     *
     * @param pos The position of the filter which is to be removed.
     */
    void removeFilter(int pos);

	/**
	 * Sets the filtered video to be controlle by this controller.
	 *
	 * @param newVideo The video to be set.
	 */
	void setVideo(::model::filter::FilteredVideo::sptr newVideo);

private:
    ::model::filter::FilteredVideo::sptr video;
	::controller::operation::OperationList list;
};

}  // namespace controller

#endif  //_FILTERCONTROLLER_H
