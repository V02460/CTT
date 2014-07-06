#if !defined(_OVERLAYCONTROLLER_H)
#define _OVERLAYCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Observer.h"
#include "SaveableList.h"
#include "Overlay.h"
#include "Video.h"

namespace controller {

/**
 * The OverlayController manages requests to manipulate the list of overlays which can be used for analyzing.
 */
class OverlayController : public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<OverlayController> uptr;
    typedef QSharedPointer<OverlayController> sptr;
    typedef QWeakPointer<OverlayController> wptr;

public slots:

    /**
     * Creates the FilterController with the Video it will observe filter changes over.
     *
     * @param video The observed video
     */
    OverlayController(::model::video::Video::sptr video);

    /**
     * Initiates the insertion of an overlay to the list of overlays which can be used for analyzing.
     * Is called when a notification is received that an overlay should be inserted.
     *
     * @param id The ID of the overlay which is to be inserted.
     */
    void insertOverlay(QString id);

    /**
     * Initiates moving a overlay to a specified position in the video's list of overlays.
     * Is called when it receives a notification that a filter should be moved.
     * Moves Filter to the end if newPos is out of bounds.
     *
     * @param oldPos The position of the filter that is to be moved.
     * @param newPos The position the filter is to be moved to.
     */
    void moveOverlay(int oldPos, int newPos);

    /**
    *    Initiates the removal of an overlay from the list of overlays which can be used for analyzing.
    *    Is called when a notification is received that an overlay should be removed.
    *    @param pos The position of the overlay which is to be removed.
    **/
    void removeOverlay(int pos);

private:
    ::model::video::Video::sptr currentVideo;
    ::model::SaveableList<::model::filter::overlay::Overlay> overlayList;
};

}  // namespace controller

#endif  //_OVERLAYCONTROLLER_H
