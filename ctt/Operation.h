#if !defined(_OPERATION_H)
#define _OPERATION_H

namespace controller {
namespace operation {

class Operation {
public:
	virtual void do() = 0;
	virtual void undo() = 0;
private:
	Operation *next;
};

}  // namespace operation
}  // namespace controller

#endif  //_OPERATION_H
