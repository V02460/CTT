


#if !defined(_FILTERCONTROLLER_H)
#define _FILTERCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Observer.h"
#include "Filter.h"
#include "FilterParam.h"
#include "FilteredVideo.h"

namespace controller {

/**
*	The FilterController receives notifications of changes in the video's filters and passes this information to all relevant components.
**/
class FilterController : public Observer {
public:
	typedef QScopedPointer<FilterController> uptr;
	typedef QSharedPointer<FilterController> sptr;
	typedef QWeakPointer<FilterController> wptr;

public slots:

	/**
	*	Initiates inserting a filter to the video's list of filters 
	*	Is called when it receives a notification that a filter should be inserted.
	*	@param id The ID of the filter that is to be added.
	**/
	void insertFilter(QString id);

	/**
	*	Initiates moving a filter to a specified position in the video's list of filters.
	*	Is called when it receives a notification that a filter should be moved.
	*	@param oldPos The position of the filter that is to be moved.
	*	@param newPos The position the filter is to be moved to.
	**/
	void moveFilter(int oldPos, int newPos);

	/**
	*	Initiates changing a filter's parameters.
	*	Is called when it receives a notification that a filterparameter should be changed.
	*	@param filter The Filter of which a parameter is to be changed.
	*	@param param The parameter which is to be changed.
	**/
	void changeFilterParam(Filter filter, FilterParam param);

	/**
	*	Initiates removing a filter from a video's list of filters.
	*	Is called when it receives a notification that a filter should be removed.
	*	@param pos The position of the filter which is to be removed.
	**/
	void removeFilter(int pos);

private:
	FilteredVideo *currentVideo;
};

}  // namespace controller

#endif  //_FILTERCONTROLLER_H
