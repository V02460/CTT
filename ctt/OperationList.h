#ifndef _OPERATIONLIST_H
#define _OPERATIONLIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"

namespace controller {
namespace operation {

/**
 * The OperationList contains a list with every Operation executed since the last load of the Project and the
 * functionality to do, undo and redo those Operations.
 */
class OperationList {
public:
    typedef QScopedPointer<OperationList> uptr;
    typedef QSharedPointer<OperationList> sptr;
    typedef QWeakPointer<OperationList> wptr;

	/**
	 * Creates a new empty operation list.
	 */
	OperationList();

	/**
	 * Destroys the operation list.
	 */
	~OperationList();

    /**
     * Manages doing the given Operation.
     *
     * @param operation The Operation that should be done.
     */
    void doOperation(Operation::sptr operation);

    /**
     * Manages undoing the Operation that has been done previously.
     */
    void undoOperation();

    /**
     * Manages redoing the Operation that has been undone previously.
     */
    void redoOperation();

    /**
     * Marks the current state as being saved last.
     */
    void markLastSavedState();

    /**
     * Determines whether there are actual changes since the last saved state.
     */
    bool hasSaveableChanges() const;

    /**
     * Determines whether an Operation has been done previously, making it possible to execute undoOperation.
     */
    bool canUndo() const;

    /**
     * Determines whether an Operation has been undone previously, making it possible to execute redoOperation.
     */
    bool canRedo() const;
private:
    QList<Operation::sptr> operations;
	QList<Operation::sptr>::iterator currentOperation;
	QList<Operation::sptr>::iterator lastSavedOperation;
};

}  // namespace operation
}  // namespace controller

#endif  //_OPERATIONLIST_H
