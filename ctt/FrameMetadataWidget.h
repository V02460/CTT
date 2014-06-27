


#if !defined(_FRAMEMETADATAWIDGET_H)
#define _FRAMEMETADATAWIDGET_H

#include "Observer.h"

class FrameMetadataWidget : public Observer {
public:
	class HistogramWidget : public Observer {
	public:
		void next();
	private:
		void paint();
	};
};

#endif  //_FRAMEMETADATAWIDGET_H
