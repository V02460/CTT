#include "OperationList.h"

#include "NotImplementedException.h"
#include "IllegalStateException.h"

namespace controller {
namespace operation {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

OperationList::OperationList() : operations(), currentOperation(0), lastSavedOperation(-1) {}

void OperationList::doOperation(Operation::sptr operation) {
	if (currentOperation < lastSavedOperation) {
		lastSavedOperation = -1;
	}
	while (currentOperation != operations.size()) {
		operations.removeLast();
	}
	operations.append(operation);
	redoOperation();
}

void OperationList::undoOperation() {
	if (!canUndo()) {
		throw IllegalStateException("There are no operations to be undone.");
	}
	currentOperation--;
	operations[currentOperation]->undoOperation();
	changed();
}

void OperationList::redoOperation() {
	if (!canRedo()) {
		throw IllegalStateException("There are no operations to be redone.");
	}
	operations[currentOperation]->doOperation();
	currentOperation++;
	changed();
}

void OperationList::markLastSavedState() {
	lastSavedOperation = currentOperation;
	// TODO changed();
}

bool OperationList::hasSaveableChanges() const {
	return lastSavedOperation != currentOperation;
}

bool OperationList::canUndo() const {
	return currentOperation != 0;
}

bool OperationList::canRedo() const {
	return currentOperation != operations.size();
}

OperationList *OperationList::getInstance() {
	if (instance.isNull()) {
		instance.reset(new OperationList());
	}
	return instance.data();
}

OperationList::uptr OperationList::instance;

}  // namespace operation
}  // namespace controller