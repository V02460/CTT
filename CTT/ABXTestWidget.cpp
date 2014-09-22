#include "ABXTestWidget.h"
#include "VideoScrubber.h"
#include <QHBoxLayout>

using model::player::Player;
using model::player::VideoScrubber;

view::ABXTestWidget::~ABXTestWidget()
{
	test->unsubscribe(this);
}

view::ABXTestWidget::ABXTestWidget(ABXController::sptr controller, QWidget *parent /*= 0*/) : QWidget(parent), controller(controller)
{
	if (controller.isNull())
	{
		throw new IllegalArgumentException("Tried to create a ABXTestWidget with a null ABXController.");
	}

	test = controller->getABXTest();
	test->subscribe(this);
	player.reset(new Player(test->getVideoA()->getMetadata().getFPS()));
	setUpUI();
}

void view::ABXTestWidget::setUpUI()
{
	mainLayout = new QGridLayout(this);

	QLabel *aLabel = new QLabel("A", this);
	QLabel *bLabel = new QLabel("B", this);
	QLabel *xLabel = new QLabel("X", this);
	QLabel *yLabel = new QLabel("Y", this);

	aLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	bLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	xLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	yLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	mainLayout->addWidget(aLabel, 0, 0);
	mainLayout->addWidget(bLabel, 0, 1);
	mainLayout->addWidget(xLabel, 2, 0);
	mainLayout->addWidget(yLabel, 2, 1);

	mainLayout->setColumnStretch(0, 1);
	mainLayout->setColumnStretch(1, 1);
	mainLayout->setColumnStretch(2, 0.2);

	statusLayout = new QVBoxLayout(this);
	triesLabel = new QLabel(tr("SUCCESSFULL_TRIES") + " : ", this);
	guessingChanceLabel = new QLabel(tr("CHANCE_THAT_YOU_WERE_GUESSING") + " : ", this);
	triesLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	guessingChanceLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	statusLayout->addWidget(triesLabel);
	statusLayout->addWidget(guessingChanceLabel);
	mainLayout->addLayout(statusLayout, 0, 2, 2, 1);

	controlsLayout = new QVBoxLayout(this);
	xIsAButton = new QPushButton(tr("X_IS_A_Y_IS_B"), this);
	xIsBButton = new QPushButton(tr("X_IS_B_Y_IS_A"), this);
	resetButton = new QPushButton(tr("RESET"), this);
	xIsAButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	xIsBButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	resetButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	statusLayout->addWidget(xIsAButton);
	statusLayout->addWidget(xIsBButton);
	controlsLayout->addStretch();
	controlsLayout->addWidget(resetButton);
	mainLayout->addLayout(controlsLayout, 2, 2, 2, 1);

	connect(resetButton, SIGNAL(clicked(bool)), controller.data(), SLOT(reset()));
	connect(xIsAButton, SIGNAL(clicked(bool)), controller.data(), SLOT(xIsA()));
	connect(xIsBButton, SIGNAL(clicked(bool)), controller.data(), SLOT(xIsB()));
	
	QHBoxLayout *playerLayout = new QHBoxLayout(this);
	playerFunctions = new PlayerFunctions(this);
	playerFunctions->setPlayer(player);
	playerLayout->addWidget(playerFunctions);
	playerLayout->addWidget(playerFunctions->getFrameSlider());
	mainLayout->addLayout(playerLayout, 4, 0, 1, 3);

	videoAContainer.reset(new QWidget);
	videoBContainer.reset(new QWidget);
	videoXContainer.reset(new QWidget);
	videoYContainer.reset(new QWidget);
	mainLayout->addWidget(videoAContainer.data(), 1, 0);
	mainLayout->addWidget(videoBContainer.data(), 1, 1);
	mainLayout->addWidget(videoXContainer.data(), 3, 0);
	mainLayout->addWidget(videoYContainer.data(), 3, 1);

	update();
}

void view::ABXTestWidget::update()
{
	triesLabel->setText(tr("SUCCESSFULL_TRIES") + " : " + QString::number(test->getNumberOfSuccessfulTries()) + "/" + QString::number(test->getNumberOfTotalTries()));
	guessingChanceLabel->setText(tr("CHANCE_THAT_YOU_WERE_GUESSING") + " : " + QString::number(test->getGuessingChance() * 100) + "%");

	mainLayout->removeWidget(videoAContainer.data());
	mainLayout->removeWidget(videoBContainer.data());
	mainLayout->removeWidget(videoXContainer.data());
	mainLayout->removeWidget(videoYContainer.data());

	VideoScrubber::sptr scrubberA(QSharedPointer<VideoScrubber>(new VideoScrubber(test->getVideoA())));
	VideoScrubber::sptr scrubberB(QSharedPointer<VideoScrubber>(new VideoScrubber(test->getVideoB())));
	VideoScrubber::sptr scrubberX(QSharedPointer<VideoScrubber>(new VideoScrubber(test->getVideoX())));
	VideoScrubber::sptr scrubberY(QSharedPointer<VideoScrubber>(new VideoScrubber(test->getVideoY())));

	if (player->getScrubbers().size() > 0)
	{
		player->removeScrubber(0);
		player->removeScrubber(0);
		player->removeScrubber(0);
		player->removeScrubber(0);
	}

	player->addScrubber(scrubberA);
	player->addScrubber(scrubberB);
	player->addScrubber(scrubberX);
	player->addScrubber(scrubberY);
	videoA.reset(new VideoWidget(scrubberA));
	videoB.reset(new VideoWidget(scrubberB));
	videoX.reset(new VideoWidget(scrubberX));
	videoY.reset(new VideoWidget(scrubberY));

	videoAContainer.reset(QWidget::createWindowContainer(videoA.data()));
	videoBContainer.reset(QWidget::createWindowContainer(videoB.data()));
	videoXContainer.reset(QWidget::createWindowContainer(videoX.data()));
	videoYContainer.reset(QWidget::createWindowContainer(videoY.data()));
	mainLayout->addWidget(videoAContainer.data(), 1, 0);
	mainLayout->addWidget(videoBContainer.data(), 1, 1);
	mainLayout->addWidget(videoXContainer.data(), 3, 0);
	mainLayout->addWidget(videoYContainer.data(), 3, 1);
}
