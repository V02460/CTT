


#if !defined(_HEATMAPOVERLAY_H)
#define _HEATMAPOVERLAY_H

#include "ColoringOverlay.h"
#include "Frame.h"
#include "Memento.h"
#include "PixelDiff.h"

class HeatmapOverlay : public ColoringOverlay {
public:
	QString getName();
	Frame getFrame(int frameNumber);
	Memento getMemento();
	void restore(Memento memento);
	Savable* getDummy();
private:
	PixelDiff* data;
};

#endif  //_HEATMAPOVERLAY_H
