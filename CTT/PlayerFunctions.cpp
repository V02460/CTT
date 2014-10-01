#include "PlayerFunctions.h"

#include <QHBoxLayout>
#include <QImageReader>
#include "PlayerController.h"

using ::model::UIntegerInterval;

namespace view {

PlayerFunctions::PlayerFunctions( QWidget *parent) : QWidget(parent) {
	sliderCurrentFrame = new QSlider();
	sliderCurrentFrame->setMinimum(0);
	sliderCurrentFrame->setOrientation(Qt::Horizontal);
	sliderCurrentFrame->setTickPosition(QSlider::TicksBelow);

	setupUi();

	subscribe(controller::PlayerController::sptr(new controller::PlayerController()));
}

PlayerFunctions::~PlayerFunctions() {
	if (!player.isNull()) {
		player->unsubscribe(this);
	}
}

void PlayerFunctions::setupUi() {
	setAccessibleName("PlayerFunctions");
	QHBoxLayout *layout = new QHBoxLayout();
	layout->setContentsMargins(0, 0, 0, 0);
	buttonSize = QSize(30, 30);
	QSizePolicy buttonSizePolicy = QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	btnPlayPause = new QPushButton(this);
	btnPlayPause->setAccessibleName("PlayerFunctions->btnPlayPause");
	btnPlayPause->setMinimumSize(buttonSize);
	btnPlayPause->setSizePolicy(buttonSizePolicy);
	layout->addWidget(btnPlayPause);
	// TODO disconnect?
	QObject::connect(btnPlayPause, SIGNAL(clicked(bool)), this, SLOT(btnPlayPauseClicked(bool)));
	layout->addSpacing(15);

	btnPreviousFrame = new QPushButton(this);
	btnPreviousFrame->setAccessibleName("PlayerFunctions->btnPreviousFrame");
	btnPreviousFrame->setMinimumSize(buttonSize);
	btnPreviousFrame->setSizePolicy(buttonSizePolicy);
	QString previousFrameIconPath = "Resources/Icons/previous.png";
	if (!QImageReader::imageFormat(previousFrameIconPath).isEmpty()) {
		btnPreviousFrame->setMaximumSize(buttonSize);
		btnPreviousFrame->setIcon(QIcon(previousFrameIconPath));
		btnPreviousFrame->setIconSize(btnPreviousFrame->size() * 0.60);
		btnPreviousFrame->setToolTip(tr("PREVIOUS_FRAME"));
	}
	else {
		btnPreviousFrame->setText(tr("PREVIOUS_FRAME"));
	}
	layout->addWidget(btnPreviousFrame);

	btnNextFrame = new QPushButton(this);
	btnNextFrame->setAccessibleName("PlayerFunctions->btnNextFrame");
	btnNextFrame->setMinimumSize(buttonSize);
	btnNextFrame->setSizePolicy(buttonSizePolicy);
	QString nextFrameIconPath = "Resources/Icons/next.png";
	if (!QImageReader::imageFormat(nextFrameIconPath).isEmpty()) {
		btnNextFrame->setMaximumSize(buttonSize);
		btnNextFrame->setIcon(QIcon(nextFrameIconPath));
		btnNextFrame->setIconSize(btnNextFrame->size() * 0.60);
		btnNextFrame->setToolTip(tr("NEXT_FRAME"));
	}
	else {
		btnNextFrame->setText(tr("NEXT_FRAME"));
	}
	layout->addWidget(btnNextFrame);

	//Must be after initialisation of btnNextFrame and btnPreviousFrame
	setPlayButton(true);

	// TODO for looping
	layout->addSpacing(15);
	btnToggleLoop = new QPushButton(this);
	btnToggleLoop->setMinimumSize(buttonSize);
	btnToggleLoop->setSizePolicy(buttonSizePolicy);
	btnToggleLoop->setText(tr("SET_LOOP_START"));
	QObject::connect(btnToggleLoop, SIGNAL(clicked()), this, SLOT(btnToggleLoopKlicked()));
	layout->addWidget(btnToggleLoop);

	layout->addStretch();

	spinboxFPS = new QDoubleSpinBox(this);
	spinboxFPS->setAccessibleName("PlayerFunctions->spinboxFPS");
	spinboxFPS->setSuffix(" FPS");
	spinboxFPS->setMinimum(0);
	spinboxFPS->setValue(0);
	layout->addWidget(spinboxFPS);

	btnDefaultFPS = new QPushButton(this);
	btnDefaultFPS->setAccessibleName("PlayerFunctions->btnDefaultFPS");
	btnDefaultFPS->setMinimumSize(10, 30);
	btnDefaultFPS->setMaximumSize(10, 30);
	btnDefaultFPS->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	btnDefaultFPS->setToolTip(tr("RESET_TO_DEFAULT_FPS"));
	layout->addWidget(btnDefaultFPS);

	setLayout(layout);
	setEnabledAll(false);
}

void PlayerFunctions::setPlayButton(bool isPlayButton) {
	if (isPlayButton) {
		QString playIconPath = "Resources/Icons/play.png";
		if (!QImageReader::imageFormat(playIconPath).isEmpty()) {
			btnPlayPause->setMaximumSize(buttonSize);
			btnPlayPause->setIcon(QIcon(playIconPath));
			btnPlayPause->setIconSize(btnNextFrame->size() * 0.60);
			btnPlayPause->setToolTip(tr("PLAY"));
		} else {
			btnPlayPause->setText(tr("PLAY"));
		}

        btnNextFrame->setEnabled(true);
		btnPreviousFrame->setEnabled(true);
	} else {
		QString pauseIconPath = "Resources/Icons/pause.png";
		if (!QImageReader::imageFormat(pauseIconPath).isEmpty()) {
			btnPlayPause->setMaximumSize(buttonSize);
			btnPlayPause->setIcon(QIcon(pauseIconPath));
			btnPlayPause->setIconSize(btnNextFrame->size() * 0.60);
			btnPlayPause->setToolTip(tr("PAUSE"));
		} else {
			btnPlayPause->setText(tr("PAUSE"));
		}

		if (player->scrubberCount() != 0) {
			btnNextFrame->setEnabled(false);
			btnPreviousFrame->setEnabled(false);
		}
	}

	this->isPlayButton = isPlayButton;
}

void PlayerFunctions::setPlayer(::model::player::Player::sptr player) {
	if (!player.isNull()) {
		if (!this->player.isNull()) {
			this->player->unsubscribe(this);
		}
		this->player = player;
		emit playerChanged(this->player);
		player->subscribe(this);
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
    btnToggleLoop->setEnabled(isEnabled);
}

QSlider* PlayerFunctions::getFrameSlider() {
	return sliderCurrentFrame;
}

void PlayerFunctions::btnPlayPauseClicked(bool checked) {
	setPlayButton(!isPlayButton);

	emit togglePlay();
}

void PlayerFunctions::btnToggleLoopKlicked() {
	QString state = btnToggleLoop->text();
	if (state == tr("SET_LOOP_START")) {
		loopStart = player->getCurrentFrameNumber();
		btnToggleLoop->setText(tr("SET_LOOP_END"));
	} else if (state == tr("SET_LOOP_END")) {
		unsigned int loopEnd = std::max(player->getCurrentFrameNumber(), loopStart);
		emit startLoop(UIntegerInterval(loopStart, loopEnd));
		btnToggleLoop->setText(tr("REMOVE_LOOP"));
	} else {
		emit endLoop();
		btnToggleLoop->setText(tr("SET_LOOP_START"));
	}
}

void PlayerFunctions::update() {
	setEnabledAll(player->scrubberCount() != 0);
	setPlayButton(!player->isPlaying());

	//Prevent call at PlayerController during update
	bool oldState = sliderCurrentFrame->blockSignals(true);
	if (player->getVideoLength() != 0) {
		sliderCurrentFrame->setMaximum(static_cast<int>(player->getVideoLength() - 1));
	}
	else {
		sliderCurrentFrame->setMaximum(0);
	}

	// TODO wtf
	try {
	    sliderCurrentFrame->setValue(static_cast<int>(player->getCurrentFrameNumber()));
	} catch (IllegalArgumentException e) {
		//Do nothing because the exception is expected
	}
	sliderCurrentFrame->blockSignals(oldState);

	sliderCurrentFrame->setTickInterval(static_cast<int>(player->getVideoLength()) / 10);



	oldState = spinboxFPS->blockSignals(true);
	spinboxFPS->setValue(player->getFPS());
	spinboxFPS->blockSignals(oldState);
}

void PlayerFunctions::subscribe(::controller::PlayerController::sptr observer) {
	QObject::connect(this, SIGNAL(togglePlay()), observer.data(), SLOT(playPause()));
	QObject::connect(btnNextFrame, SIGNAL(clicked()), observer.data(), SLOT(nextFrame()));
	QObject::connect(btnPreviousFrame, SIGNAL(clicked()), observer.data(), SLOT(previousFrame()));
	QObject::connect(sliderCurrentFrame, SIGNAL(valueChanged(int)), observer.data(), SLOT(currentFrameChanged(int)));
	QObject::connect(btnDefaultFPS, SIGNAL(clicked()), observer.data(), SLOT(setToDefaultFPS()));
	QObject::connect(spinboxFPS, SIGNAL(valueChanged(double)), observer.data(), SLOT(setFPS(double)));
	QObject::connect(this, SIGNAL(playerChanged(::model::player::Player::sptr)), observer.data(),
		SLOT(setPlayer(::model::player::Player::sptr)));
	QObject::connect(this, SIGNAL(startLoop(::model::UIntegerInterval)), observer.data(), SLOT(createLoop(::model::UIntegerInterval)));
	QObject::connect(this, SIGNAL(endLoop()), observer.data(), SLOT(terminateLoop()));

	this->playerController = observer;

	emit playerChanged(player);
}

void PlayerFunctions::unsubscribe(const ::controller::PlayerController &observer) {
	QObject::disconnect(this, SIGNAL(togglePlay()), &observer, SLOT(playPause()));
	QObject::disconnect(btnNextFrame, SIGNAL(clicked()), &observer, SLOT(nextFrame()));
	QObject::disconnect(btnPreviousFrame, SIGNAL(clicked()), &observer, SLOT(previousFrame()));
	QObject::disconnect(sliderCurrentFrame, SIGNAL(valueChanged(int)), &observer, SLOT(currentFrameChanged(int)));
	QObject::disconnect(btnDefaultFPS, SIGNAL(clicked()), &observer, SLOT(setToDefaultFPS()));
	QObject::disconnect(spinboxFPS, SIGNAL(valueChanged(double)), &observer, SLOT(setFPS(double)));
	QObject::disconnect(this, SIGNAL(playerChanged(::model::player::Player::sptr)), &observer,
		SLOT(setPlayer(::model::player::Player::sptr)));
	QObject::disconnect(this, SIGNAL(startLoop(::model::UIntegerInterval)), &observer, SLOT(createLoop(::model::UIntegerInterval)));
	QObject::disconnect(this, SIGNAL(endLoop()), &observer, SLOT(terminateLoop()));

	this->playerController = ::controller::PlayerController::sptr();
}

}  // namespace view