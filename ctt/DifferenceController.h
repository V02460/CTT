#if !defined(_DIFFERENCECONTROLLER_H)
#define _DIFFERENCECONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Observer.h"
#include "SaveableList.h"

namespace controller {

/**
 * The DifferenceController manages requests to manipulate the list of difference functions.
 */
class DifferenceController : public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<DifferenceController> uptr;
    typedef QSharedPointer<DifferenceController> sptr;
    typedef QWeakPointer<DifferenceController> wptr;

public slots:

    /**
     * Initiates the insertion of a difference function to the list of difference functions which is used for analyzing.
     * Is called when a notification is received that a difference function should be inserted.
     *
     * @param id The ID of the difference function which is to be inserted.
     */
    void diffInserted(QString id);

    /**
     * Initiates the removal of a difference function from the list of difference functions which is used for analyzing.
     * Is called when a notification is received that a difference function should be removed.
     *
     * @param pos The position of the difference function which is to be removed.
     */
    void diffRemoved(int pos);
private:
    ::model::SaveableList<::model::project::Saveable> diffList;
};

}  // namespace controller

#endif  //_DIFFERENCECONTROLLER_H
