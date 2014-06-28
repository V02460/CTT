


#if !defined(_RGBCHANNELFILTER_H)
#define _RGBCHANNELFILTER_H

#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

class RGBChannelFilter : public Filter {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_RGBCHANNELFILTER_H
