


#if !defined(_FRAMEDIFF_H)
#define _FRAMEDIFF_H

#include "Saveable.h"
#include "Video.h"
#include "Memento.h"

class FrameDiff : public Saveable {
public:
	virtual double getDif(int frameNr);

	virtual Memento getMemento();
	virtual void restore(Memento memento);
protected:
	Video video1;
	Video video2;
};

#endif  //_FRAMEDIFF_H
