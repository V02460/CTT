


#if !defined(_COLORINGOVERLAY_H)
#define _COLORINGOVERLAY_H

#include "Overlay.h"
#include "Frame.h"
#include "Memento.h"

class ColoringOverlay : public Overlay {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Saveable* getDummy();
};

#endif  //_COLORINGOVERLAY_H
