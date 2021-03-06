#ifndef _OPERATIONLIST_H
#define _OPERATIONLIST_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "Observable.h"

namespace controller {
namespace operation {

/**
 * The OperationList contains a list with every Operation executed since the last load of the Project and the
 * functionality to do, undo and redo those Operations.
 */
class OperationList : public ::model::Observable {
public:
    typedef QScopedPointer<OperationList> uptr;
    typedef QSharedPointer<OperationList> sptr;
    typedef QWeakPointer<OperationList> wptr;

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

	/**
	 * Removes all Operations from the list and resets the lastSavedState and currentOperation.
	 */
	void clear();

	/**
	 * Determines whether this is a new Project or not
	 */
	bool isNew() const;

	/**
	 * Returns the one instance this class can have.
	 */
	static OperationList *getInstance();

private:
	Q_DISABLE_COPY(OperationList)

	OperationList();

	static OperationList::uptr instance;

    QList<Operation::sptr> operations;
	int currentOperation;
	int lastSavedOperation;
};

}  // namespace operation
}  // namespace controller

#endif  //_OPERATIONLIST_H
