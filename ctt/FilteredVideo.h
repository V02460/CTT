


#if !defined(_FILTEREDVIDEO_H)
#define _FILTEREDVIDEO_H

#include "Video.h"
#include "Observable.h"
#include "Filter.h"
#include "FilterList.h"
#include "Frame.h"
#include "Memento.h"

class FilteredVideo : public Video, public Observable {
public:
	void FilteredVideo(Video baseVideo);
	void addFilter(Filter filter, int pos);
	Filter removeFilter(int pos);
	int getFilterCount();
	FilterList getFilterList();
	VideoMetadata getMetadata();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
private:
	Video *baseVideo;
	FilterList *filters;
};

#endif  //_FILTEREDVIDEO_H
