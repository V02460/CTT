#include "OperationList.h"

#include "NotImplementedException.h"
#include "IllegalStateException.h"

namespace controller {
namespace operation {

using ::exception::NotImplementedException;
using ::exception::IllegalStateException;

OperationList::OperationList() : currentOperation(operations.begin()) {}

//OperationList::~OperationList() {}

void OperationList::doOperation(Operation::sptr operation) {
	/* TODO
	 * off by one?
	 * consistent?
	 * delete nur wenn nötig für performance?
	 */
	currentOperation = operations.erase(currentOperation, operations.end() - 1);
	operations.append(operation);
	operation->doOperation();
}

void OperationList::undoOperation() {
	if (!canUndo()) {
		throw new IllegalStateException("There are no operations to be undone.");
	}
	currentOperation--;
	currentOperation[0]->undoOperation();
}

void OperationList::redoOperation() {
	if (!canRedo()) {
		throw new IllegalStateException("There are no operations to be redone.");
	}
	currentOperation[0]->doOperation();
	currentOperation++;
}

void OperationList::markLastSavedState() {
	lastSavedOperation = currentOperation;
}

bool OperationList::hasSaveableChanges() const {
	return lastSavedOperation != currentOperation;
}

bool OperationList::canUndo() const {
	return currentOperation != operations.constBegin();
}

bool OperationList::canRedo() const {
	return currentOperation != operations.constEnd();
}

OperationList::sptr OperationList::getInstance() {
	if (instance.isNull()) {
		instance = QSharedPointer<OperationList>(new OperationList());
	}
	return instance;
}

OperationList::sptr OperationList::instance = OperationList::getInstance();

}  // namespace operation
}  // namespace controller