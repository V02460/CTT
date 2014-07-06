#if !defined(_FILTERTIMELINE_H)
#define _FILTERTIMELINE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "AbstractTimeline.h"

namespace view {

/**
 * The FilterTimeline displays the filter intervals of ervery filter of a filteredVideo.
 * Each interval is painted as a bar which is moveable within the video.
 */
class FilterTimeline : public AbstractTimeline {
public:
    typedef QScopedPointer<FilterTimeline> uptr;
    typedef QSharedPointer<FilterTimeline> sptr;
    typedef QWeakPointer<FilterTimeline> wptr;

};


}  // namespace view

class FilterTimeline
{
public:
	FilterTimeline();
	~FilterTimeline();
};

#endif  //_FILTERTIMELINE_H
