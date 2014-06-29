#if !defined(_FPSCHANGINGOPERATION_H)
#define _FPSCHANGINGOPERATION_H

#include "Operation.h"

namespace controller {
namespace operation {

class FPSChangingOperation : public Operation {
public:
	signal FPSChanged(double fps);
	void do();
	void undo();
private:
	double oldFPS;
	double newFPS;
};

}  // namespace operation
}  // namespace controller

#endif  //_FPSCHANGINGOPERATION_H
