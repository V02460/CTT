#ifndef _DIFFERENCECONTROLLER_H
#define _DIFFERENCECONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>

#include "Observer.h"
#include "SaveableList.h"

namespace controller {

/**
 * The DifferenceController manages requests to manipulate the list of difference functions.
 */
class DifferenceController : public QObject, public ::model::Observer {
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
void diffInserted(QString id, Video::sptr video1, Video::sptr video2);

    /**
     * Initiates the removal of a difference function from the list of difference functions which is used for analyzing.
     * Is called when a notification is received that a difference function should be removed.
     *
     * @param pos The position of the difference function which is to be removed.
     */
    void diffRemoved(int pos);
private:
    ::model::saveable::SaveableList<::model::saveable::Saveable> diffList;
};

}  // namespace controller

#endif  //_DIFFERENCECONTROLLER_H
