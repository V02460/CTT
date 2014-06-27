


#if !defined(_MACROPARTITIONOVERLAY_H)
#define _MACROPARTITIONOVERLAY_H

#include "Overlay.h"
#include "Frame.h"
#include "Memento.h"

class MacropartionOverlay : public Overlay {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
};

#endif  //_MACROPARTITIONOVERLAY_H
