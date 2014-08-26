#include "PlayerFunctions.h"

#include <QHBoxLayout>
#include "PlayerController.h"

namespace view {

PlayerFunctions::PlayerFunctions( QWidget *parent) : QWidget(parent) {
	sliderCurrentFrame = new QSlider();
	sliderCurrentFrame->setMinimum(0);
	sliderCurrentFrame->setOrientation(Qt::Horizontal);
	sliderCurrentFrame->setTickPosition(QSlider::TicksBelow);

	setupUi();

	subscribe(controller::PlayerController::sptr(new controller::PlayerController()));
}

void PlayerFunctions::setupUi() {
	setAccessibleName("PlayerFunctions");
	QHBoxLayout *layout = new QHBoxLayout();
	QSize buttonSize = QSize(30, 30);
	QSizePolicy buttonSizePolicy = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	btnPlayPause = new QPushButton(this);
	btnPlayPause->setAccessibleName("PlayerFunctions->btnPlayPause");
	btnPlayPause->setMinimumSize(buttonSize);
	btnPlayPause->setSizePolicy(buttonSizePolicy);
	layout->addWidget(btnPlayPause);
	QObject::connect(btnPlayPause, SIGNAL(clicked(bool)), this, SLOT(btnPlayPauseClicked(bool)));

	btnPreviousFrame = new QPushButton(this);
	btnPreviousFrame->setAccessibleName("PlayerFunctions->btnPreviousFrame");
	btnPreviousFrame->setMinimumSize(buttonSize);
	btnPreviousFrame->setSizePolicy(buttonSizePolicy);
	layout->addWidget(btnPreviousFrame);
	btnPreviousFrame->setText(tr("PREVIOUS_FRAME"));

	btnNextFrame = new QPushButton(this);
	btnNextFrame->setAccessibleName("PlayerFunctions->btnNextFrame");
	btnNextFrame->setMinimumSize(buttonSize);
	btnNextFrame->setSizePolicy(buttonSizePolicy);
	layout->addWidget(btnNextFrame);
	btnNextFrame->setText(tr("NEXT_FRAME"));

	//Must be after initialisation of btnNextFrame and btnPreviousFrame
	setPlayButton(true);

	layout->addStretch();

	spinboxFPS = new QSpinBox(this);
	spinboxFPS->setAccessibleName("PlayerFunctions->spinboxFPS");
	spinboxFPS->setSuffix(" FPS");
	spinboxFPS->setMinimum(0);
	spinboxFPS->setValue(0);
	layout->addWidget(spinboxFPS);

	btnDefaultFPS = new QPushButton(this);
	btnDefaultFPS->setAccessibleName("PlayerFunctions->btnDefaultFPS");
	btnDefaultFPS->setMinimumSize(10, 30);
	btnDefaultFPS->setSizePolicy(buttonSizePolicy);
	btnDefaultFPS->setToolTip(tr("RESET_TO_DEFAULT_FPS"));
	layout->addWidget(btnDefaultFPS);
	btnDefaultFPS->setText(tr("DEFAULT_FPS"));

	setLayout(layout);
}

void PlayerFunctions::setPlayButton(bool isPlayButton) {
	if (isPlayButton) {
		btnPlayPause->setText(tr("PLAY"));
		btnNextFrame->setEnabled(true);
		btnPreviousFrame->setEnabled(true);
	} else {
		btnPlayPause->setText(tr("PAUSE"));
		btnNextFrame->setEnabled(false);
		btnPreviousFrame->setEnabled(false);
	}

	this->isPlayButton = isPlayButton;
}

void PlayerFunctions::setPlayer(::model::player::Player::sptr player) {
	if (!player.isNull()) {
		//this->player->unsubscribe(*this);

		this->player = player;
		emit playerChanged(this->player);
	
		player->subscribe(this);

		sliderCurrentFrame->setMaximum(static_cast<int>(player->getVideoLength()));
		sliderCurrentFrame->setValue(static_cast<int>(player->getCurrentFrameNumber()));
		sliderCurrentFrame->setTickInterval(static_cast<int>(player->getVideoLength()) / 10);

		setEnabledAll(true);

		update();
	} else {
		qDebug() << "Error in PlayerFunctions! Player to be set was empty.";
	}
}

void PlayerFunctions::removePlayer() {
	setEnabledAll(false);
}

void PlayerFunctions::setEnabledAll(bool isEnabled) {
	btnPlayPause->setEnabled(isEnabled);
	btnPreviousFrame->setEnabled(isEnabled);
	btnNextFrame->setEnabled(isEnabled);
	btnDefaultFPS->setEnabled(isEnabled);
	spinboxFPS->setEnabled(isEnabled);
	sliderCurrentFrame->setEnabled(isEnabled);
}

QSlider* PlayerFunctions::getFrameSlider() {
	return sliderCurrentFrame;
}

void PlayerFunctions::btnPlayPauseClicked(bool checked) {
	setPlayButton(!isPlayButton);

	emit togglePlay();
}

void PlayerFunctions::update() {
	setPlayButton(!player->isPlaying());

	sliderCurrentFrame->setValue(static_cast<int>(player->getCurrentFrameNumber()));

	spinboxFPS->setValue(player->getFPS());
}

void PlayerFunctions::subscribe(::controller::PlayerController::sptr observer) {
	QObject::connect(this, SIGNAL(togglePlay()), observer.data(), SLOT(playPause()));
	QObject::connect(btnNextFrame, SIGNAL(clicked()), observer.data(), SLOT(nextFrame()));
	QObject::connect(btnPreviousFrame, SIGNAL(clicked()), observer.data(), SLOT(previousFrame()));
	QObject::connect(sliderCurrentFrame, SIGNAL(sliderMoved(int)), observer.data(), SLOT(currentFrameChanged(int)));
	QObject::connect(btnDefaultFPS, SIGNAL(clicked()), observer.data(), SLOT(setToDefaultFPS()));
	QObject::connect(spinboxFPS, SIGNAL(valueChanged(int)), observer.data(), SLOT(setFPS(int)));
	QObject::connect(this, SIGNAL(playerChanged(::model::player::Player::sptr)), observer.data(),
		SLOT(setPlayer(::model::player::Player::sptr)));

	this->playerController = observer;

	emit playerChanged(player);
}

void PlayerFunctions::unsubscribe(const ::controller::PlayerController &observer) {
	QObject::disconnect(this, SIGNAL(togglePlay()), &observer, SLOT(playPause()));
	QObject::disconnect(btnNextFrame, SIGNAL(clicked()), &observer, SLOT(nextFrame()));
	QObject::disconnect(btnPreviousFrame, SIGNAL(clicked()), &observer, SLOT(previousFrame()));
	QObject::disconnect(sliderCurrentFrame, SIGNAL(sliderMoved(int)), &observer, SLOT(currentFrameChanged(int)));
	QObject::disconnect(btnDefaultFPS, SIGNAL(clicked()), &observer, SLOT(setToDefaultFPS()));
	QObject::disconnect(spinboxFPS, SIGNAL(valueChanged(int)), &observer, SLOT(setFPS(int)));
	QObject::disconnect(this, SIGNAL(playerChanged(::model::player::Player::sptr)), &observer,
		SLOT(setPlayer(::model::player::Player::sptr)));

	this->playerController = ::controller::PlayerController::sptr();
}

}  // namespace view