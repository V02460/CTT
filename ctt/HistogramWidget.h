


#if !defined(_HISTOGRAMWIDGET_H)
#define _HISTOGRAMWIDGET_H

#include "Observer.h"

class HistogramWidget : public Observer {
public:
	void next();
private:
	void paint();
};

#endif  //_HISTOGRAMWIDGET_H