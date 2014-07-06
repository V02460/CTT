#if !defined(_PLAYERFUNCTIONS_H)
#define _PLAYERFUNCTIONS_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>

#include "Observable.h"
#include "PlayerController.h"

namespace view {

/**
 * The PlayerFunctions only provides the needed interactable components and maps the signals emitted by these to a
 * PlayerController.
 */
class PlayerFunctions : public ::model::Observable , public QWidget{
    Q_OBJECT
public:
    typedef QScopedPointer<PlayerFunctions> uptr;
    typedef QSharedPointer<PlayerFunctions> sptr;
    typedef QWeakPointer<PlayerFunctions> wptr;

    /**
     * Connects the signals from the interactable components to the corresponding slots in a PlayerController.
     *
     * @param observer The PlayerController the signals should be connected to.
     */
    void subscribe(::controller::PlayerController::sptr observer);

    /**
     * Disconnects the signals from the interactable components to the corresponding slots in a PlayerController.
     *
     * @param observer The PlayerController the signals should be disconnected from.
     */
    void unsubscribe(const ::controller::PlayerController &observer);
private:
    QPushButton btnPlayPause; /**< The button to play/pause the player */
    QPushButton btnNextFrame; /**< The button to go to the next frame */
    QPushButton btnPreviousFrame; /**< The button to go to the previous frame */
    QPushButton btnDefaultFPS; /**< The button to change back to the default framerate */
    QSpinBox spinboxFPS; /**< The spinbox to change the framerate */
};

}  // namespace view

#endif  //_PLAYERFUNCTIONS_H
