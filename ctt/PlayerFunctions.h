#ifndef _PLAYERFUNCTIONS_H
#define _PLAYERFUNCTIONS_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QSlider>

#include "Observable.h"
#include "PlayerController.h"

namespace view {

/**
 * The PlayerFunctions only provides the needed intractable components and maps the signals emitted by these to a
 * PlayerController.
 */
class PlayerFunctions : public QWidget, public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<PlayerFunctions> uptr;
    typedef QSharedPointer<PlayerFunctions> sptr;
    typedef QWeakPointer<PlayerFunctions> wptr;

	PlayerFunctions(QWidget *parent = 0);

	~PlayerFunctions();

	QSlider* getFrameSlider();

	void setPlayer(::model::player::Player::sptr player);
	void removePlayer();

	void setEnabledAll(bool isEnabled);
    /**
     * Connects the signals from the intractable components to the corresponding slots in a PlayerController.
     *
     * @param observer The PlayerController the signals should be connected to.
     */
    void subscribe(::controller::PlayerController::sptr observer);

    /**
     * Disconnects the signals from the intractable components to the corresponding slots in a PlayerController.
     *
     * @param observer The PlayerController the signals should be disconnected from.
     */
    void unsubscribe(const ::controller::PlayerController &observer);

	virtual void update() Q_DECL_OVERRIDE;
public slots:
	void btnPlayPauseClicked(bool checked);
signals:
	void togglePlay();
	void playerChanged(::model::player::Player::sptr player);
private:
	void setupUi();
	void setPlayButton(bool isPlayButton);

	::model::player::Player::sptr player;
	bool isPlayButton;

    QPushButton *btnPlayPause; /**< The button to play/pause the player */
    QPushButton *btnNextFrame; /**< The button to go to the next frame */
    QPushButton *btnPreviousFrame; /**< The button to go to the previous frame */
    QPushButton *btnDefaultFPS; /**< The button to change back to the default frame rate */
    QDoubleSpinBox *spinboxFPS; /**< The spin box to change the frame rate */
	QSlider *sliderCurrentFrame;
	QSize buttonSize;

	::controller::PlayerController::sptr playerController;
};

}  // namespace view

#endif  //_PLAYERFUNCTIONS_H
