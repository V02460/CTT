#include "OperationList.h"

#include "NotImplementedException.h"

namespace controller {
namespace operation {

using ::exception::NotImplementedException;

void OperationList::doOperation(Operation::sptr operation) {
    throw new NotImplementedException();
}

void OperationList::undoOperation() {
    throw new NotImplementedException();
}

void OperationList::redoOperation() {
    throw new NotImplementedException();
}

void OperationList::setLastSavedState() {
    throw new NotImplementedException();
}

bool OperationList::hasSaveableChanges() const {
    throw new NotImplementedException();
}

bool OperationList::canUndo() const {
    throw new NotImplementedException();
}

bool OperationList::canRedo() const {
    throw new NotImplementedException();
}

}  // namespace operation
}  // namespace controller