


#if !defined(_MOTIONVECTOROVERLAY_H)
#define _MOTIONVECTOROVERLAY_H

#include "Overlay.h"
#include "Frame.h"
#include "Memento.h"

class MotionVectorOverlay : public Overlay {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_MOTIONVECTOROVERLAY_H
