


#if !defined(_FPSCHANGINGOPERATION_H)
#define _FPSCHANGINGOPERATION_H

#include "Operation.h"

class FPSChangingOperation : public Operation {
public:
	signal FPSChanged(double fps);
	void do();
	void undo();
private:
	double oldFPS;
	double newFPS;
};

#endif  //_FPSCHANGINGOPERATION_H
