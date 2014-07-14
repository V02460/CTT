#include "ProcessingWidget.h"
#include "MathHelper.h"

namespace view {

ProcessingWidget::ProcessingWidget(controller::project::Project *project, QWidget *parent) {
	this->setParent(parent);
	this->players = project->getPlayerList1();
	playerWidgets = new QList<PlayerWidget>();
	thumbnailWidget = new ThumbnailListWidget(players, this);
	//TODO Setze richtigen Player ein
	displayedPlayerWidget = new PlayerWidget(new model::player::Player(25), this);
	update();
	setupUi();
}

void ProcessingWidget::update() {

}

void ProcessingWidget::setupUi() {
	if (this->objectName().isEmpty())
		this->setObjectName(QStringLiteral("ProcessingWidget"));
	//this->resize(800, 600);
	mainVerticalLayout = new QVBoxLayout(this);
	mainVerticalLayout->setSpacing(5);
	mainVerticalLayout->setObjectName(QStringLiteral("mainVerticalLayout"));
	mainVerticalLayout->setContentsMargins(0, 0, 0, 0);
	verticalSplitter = new QSplitter(this);
	verticalSplitter->setObjectName(QStringLiteral("verticalSplitter"));
	verticalSplitter->setFrameShape(QFrame::NoFrame);
	verticalSplitter->setOrientation(Qt::Vertical);
	verticalSplitter->setHandleWidth(5);
	upperWidget = new QWidget(verticalSplitter);
	upperWidget->setObjectName(QStringLiteral("upperWidget"));
	QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(1);
	sizePolicy.setHeightForWidth(upperWidget->sizePolicy().hasHeightForWidth());
	upperWidget->setSizePolicy(sizePolicy);
	upperHorizontalLayout = new QHBoxLayout(upperWidget);
	upperHorizontalLayout->setObjectName(QStringLiteral("upperHorizontalLayout"));
	upperHorizontalLayout->setContentsMargins(0, 0, 0, 0);
	upperHorizontalSplitter = new QSplitter(upperWidget);
	upperHorizontalSplitter->setObjectName(QStringLiteral("upperHorizontalSplitter"));
	QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
	sizePolicy1.setHorizontalStretch(1);
	sizePolicy1.setVerticalStretch(0);
	sizePolicy1.setHeightForWidth(upperHorizontalSplitter->sizePolicy().hasHeightForWidth());
	upperHorizontalSplitter->setSizePolicy(sizePolicy1);
	upperHorizontalSplitter->setFrameShape(QFrame::NoFrame);
	upperHorizontalSplitter->setOrientation(Qt::Horizontal);
	upperHorizontalSplitter->setHandleWidth(5);
	upperHorizontalSplitter->setChildrenCollapsible(false);
	videoAddWidget = new QWidget(upperHorizontalSplitter);
	videoAddWidget->setObjectName(QStringLiteral("videoAddWidget"));
	QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy2.setHorizontalStretch(1);
	sizePolicy2.setVerticalStretch(0);
	sizePolicy2.setHeightForWidth(videoAddWidget->sizePolicy().hasHeightForWidth());
	videoAddWidget->setSizePolicy(sizePolicy2);
	videoAddWidget->setMinimumSize(QSize(150, 0));
	thumbnailListVerticalLayout = new QVBoxLayout(videoAddWidget);
	thumbnailListVerticalLayout->setObjectName(QStringLiteral("thumbnailListVerticalLayout"));
	thumbnailListVerticalLayout->setContentsMargins(0, 0, 0, 0);
	scrollArea = new QScrollArea(videoAddWidget);
	scrollArea->setObjectName(QStringLiteral("scrollArea"));
	scrollArea->setWidgetResizable(true);
	scrollAreaThumbnailList = new QWidget();
	scrollAreaThumbnailList->setObjectName(QStringLiteral("scrollAreaThumbnailList"));
	//scrollAreaThumbnailList->setGeometry(QRect(0, 0, 148, 397));
	scrollAreaVerticalLayout = new QVBoxLayout(scrollAreaThumbnailList);
	scrollAreaVerticalLayout->setSpacing(5);
	scrollAreaVerticalLayout->setObjectName(QStringLiteral("scrollAreaVerticalLayout"));
	scrollAreaVerticalLayout->setContentsMargins(0, 0, 0, 0);
	thumbnailWidget->setObjectName(QStringLiteral("tumbnailListWidget"));

	scrollAreaVerticalLayout->addWidget(thumbnailWidget);

	scrollArea->setWidget(scrollAreaThumbnailList);

	thumbnailListVerticalLayout->addWidget(scrollArea);

	switchStateWidget = new QWidget(videoAddWidget);
	switchStateWidget->setObjectName(QStringLiteral("switchStateWidget"));
	switchStateHoritzontalLayout = new QHBoxLayout(switchStateWidget);
	switchStateHoritzontalLayout->setObjectName(QStringLiteral("switchStateHoritzontalLayout"));
	switchStateHoritzontalLayout->setContentsMargins(0, 0, 0, 0);
	switchStateSpacerleft = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	switchStateHoritzontalLayout->addItem(switchStateSpacerleft);

	switchStateButton = new QPushButton(switchStateWidget);
	switchStateButton->setObjectName(QStringLiteral("switchStateButton"));
	QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
	sizePolicy3.setHorizontalStretch(0);
	sizePolicy3.setVerticalStretch(0);
	sizePolicy3.setHeightForWidth(switchStateButton->sizePolicy().hasHeightForWidth());
	switchStateButton->setSizePolicy(sizePolicy3);
	switchStateButton->setMinimumSize(QSize(150, 0));

	switchStateHoritzontalLayout->addWidget(switchStateButton);

	switchStateSpacerRight = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	switchStateHoritzontalLayout->addItem(switchStateSpacerRight);


	thumbnailListVerticalLayout->addWidget(switchStateWidget);

	upperHorizontalSplitter->addWidget(videoAddWidget);
	displayFrame = new QFrame(upperHorizontalSplitter);
	displayFrame->setObjectName(QStringLiteral("displayFrame"));
	QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy4.setHorizontalStretch(255);
	sizePolicy4.setVerticalStretch(0);
	sizePolicy4.setHeightForWidth(displayFrame->sizePolicy().hasHeightForWidth());
	displayFrame->setSizePolicy(sizePolicy4);
	displayFrame->setMinimumSize(QSize(0, 0));
	displayFrame->setFrameShape(QFrame::StyledPanel);
	displayHorizontalLayout = new QHBoxLayout(displayFrame);
	displayHorizontalLayout->setObjectName(QStringLiteral("displayHorizontalLayout"));
	displayHorizontalLayout->setContentsMargins(0, 0, 0, 0);
	displayedPlayerWidget->setObjectName(QStringLiteral("displayedPlayerWidget"));

	displayHorizontalLayout->addWidget(displayedPlayerWidget);

	upperHorizontalSplitter->addWidget(displayFrame);

	upperHorizontalLayout->addWidget(upperHorizontalSplitter);

	verticalSplitter->addWidget(upperWidget);
	controlsFrame = new QFrame(verticalSplitter);
	controlsFrame->setObjectName(QStringLiteral("controlsFrame"));
	QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy5.setHorizontalStretch(0);
	sizePolicy5.setVerticalStretch(20);
	sizePolicy5.setHeightForWidth(controlsFrame->sizePolicy().hasHeightForWidth());
	controlsFrame->setSizePolicy(sizePolicy5);
	controlsFrame->setFrameShape(QFrame::StyledPanel);
	controlsHorizontalLayout = new QHBoxLayout(controlsFrame);
	controlsHorizontalLayout->setObjectName(QStringLiteral("controlsHorizontalLayout"));
	controlsHorizontalLayout->setContentsMargins(0, 0, 0, 0);
	lowHorizontalSplitter = new QSplitter(controlsFrame);
	lowHorizontalSplitter->setObjectName(QStringLiteral("lowHorizontalSplitter"));
	sizePolicy1.setHeightForWidth(lowHorizontalSplitter->sizePolicy().hasHeightForWidth());
	lowHorizontalSplitter->setSizePolicy(sizePolicy1);
	lowHorizontalSplitter->setOrientation(Qt::Horizontal);
	lowHorizontalSplitter->setHandleWidth(0);
	lowHorizontalSplitter->setChildrenCollapsible(false);
	lowerLeftWidget = new QWidget(lowHorizontalSplitter);
	lowerLeftWidget->setObjectName(QStringLiteral("lowerLeftWidget"));
	sizePolicy2.setHeightForWidth(lowerLeftWidget->sizePolicy().hasHeightForWidth());
	lowerLeftWidget->setSizePolicy(sizePolicy2);
	lowerLeftWidget->setMinimumSize(QSize(250, 0));
	mainControlHorizontalLayout = new QHBoxLayout(lowerLeftWidget);
	mainControlHorizontalLayout->setSpacing(0);
	mainControlHorizontalLayout->setObjectName(QStringLiteral("mainControlHorizontalLayout"));
	mainControlHorizontalLayout->setContentsMargins(0, 0, 0, 0);
	mainControlWidget = new MainControlWidget(lowerLeftWidget);
	mainControlWidget->setObjectName(QStringLiteral("mainControlWidget"));

	mainControlHorizontalLayout->addWidget(mainControlWidget);

	line = new QFrame(lowerLeftWidget);
	line->setObjectName(QStringLiteral("line"));
	line->setFrameShape(QFrame::VLine);
	line->setFrameShadow(QFrame::Sunken);

	mainControlHorizontalLayout->addWidget(line);

	lowHorizontalSplitter->addWidget(lowerLeftWidget);
	lowerRightWidget = new QWidget(lowHorizontalSplitter);
	lowerRightWidget->setObjectName(QStringLiteral("lowerRightWidget"));
	QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy6.setHorizontalStretch(3);
	sizePolicy6.setVerticalStretch(0);
	sizePolicy6.setHeightForWidth(lowerRightWidget->sizePolicy().hasHeightForWidth());
	lowerRightWidget->setSizePolicy(sizePolicy6);
	extendedTimelineHorizontalLayout = new QHBoxLayout(lowerRightWidget);
	extendedTimelineHorizontalLayout->setSpacing(0);
	extendedTimelineHorizontalLayout->setObjectName(QStringLiteral("extendedTimelineHorizontalLayout"));
	extendedTimelineHorizontalLayout->setContentsMargins(0, 0, 0, 0);
	line_2 = new QFrame(lowerRightWidget);
	line_2->setObjectName(QStringLiteral("line_2"));
	line_2->setFrameShape(QFrame::VLine);
	line_2->setFrameShadow(QFrame::Sunken);

	extendedTimelineHorizontalLayout->addWidget(line_2);

	extendedTimeline = new ExtendedTimeline(lowerRightWidget);
	extendedTimeline->setObjectName(QStringLiteral("extendedTimeline"));

	extendedTimelineHorizontalLayout->addWidget(extendedTimeline);

	lowHorizontalSplitter->addWidget(lowerRightWidget);

	controlsHorizontalLayout->addWidget(lowHorizontalSplitter);

	verticalSplitter->addWidget(controlsFrame);

	mainVerticalLayout->addWidget(verticalSplitter);


	retranslateUi();

	QMetaObject::connectSlotsByName(this);
} // setupUi

void ProcessingWidget::retranslateUi()
{
	this->setWindowTitle(QApplication::translate("ProcessingWidget", "Form", 0));
	switchStateButton->setText(QApplication::translate("ProcessingWidget", "SWITCH_TO_ANALYSIS", 0));
} // retranslateUi

void ProcessingWidget::activatePlayer(const PlayerWidget &playerWidget) {

}

}  // namespace view