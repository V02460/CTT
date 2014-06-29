#if !defined(_PLAYERFUNCTIONS_H)
#define _PLAYERFUNCTIONS_H

#include "Observable.h"
#include "PlayerController.h"
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>

namespace view {

/**
 *	The PlayerFunctions only provides the needed interactable components and maps the signals emitted by these to a PlayerController
 */
class PlayerFunctions : public Observable , public QWidget{
public:
	/**
	 *	Connects the signals from the interactable components to the corresponding slots in a PlayerController
	 *
	 *	@param the PlayerController the signals should be connected to
	 */
	void subscribe(PlayerController observer);
	/**
	 *	Disconnects the signals from the interactable components to the corresponding slots in a PlayerController
	 *
	 *	@param the PlayerController the signals should be disconnected from
	 */
	void unsubscribe(PlayerController observer);
private:
	QPushButton btnPlayPause; /**< The button to play/pause the player */
	QPushButton btnNextFrame; /**< The button to go to the next frame */
	QPushButton btnPreviousFrame; /**< The button to go to the previous frame */
	QPushButton btnDefaultFPS; /**< The button to change back to the default framerate */
	QSpinBox spinboxFPS; /**< The spinbox to change the framerate */
};

}  // namespace view

#endif  //_PLAYERFUNCTIONS_H
