


#if !defined(_MACROBLOCKOVERLAY_H)
#define _MACROBLOCKOVERLAY_H

#include "ColoringOverlay.h"
#include "Frame.h"
#include "Memento.h"

class MacroblockOverlay : public ColoringOverlay {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_MACROBLOCKOVERLAY_H
