


#if !defined(_FILTERCONTROLLER_H)
#define _FILTERCONTROLLER_H

#include "Observer.h"
#include "Filter.h"
#include "FilterParam.h"
#include "FilteredVideo.h"

class FilterController : public Observer {
public:
	slot insertFilter(QString id);
	slot moveFilter(int oldPos, int newPos);
	slot changeFilterParam(Filter filter, FilterParam param);
	slot removeFilter(int pos);
private:
	FilteredVideo *currentVideo;
};

#endif  //_FILTERCONTROLLER_H
