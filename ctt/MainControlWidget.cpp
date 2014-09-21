#include "MainControlWidget.h"

#include <QLayout>
#include <QFrame>
#include <QScrollArea>
#include <QSplitter>

#include "FilterInsertionWidget.h"
#include "FilterListView.h"
#include "DifferenceInsertionWidget.h"
#include "DifferenceListView.h"
#include "DifferenceTimeline.h"
#include "DifferenceController.h"
#include "NotImplementedException.h"

using ::controller::FilterController;
using ::controller::DifferenceController;
using ::model::player::Player;
using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;
using ::controller::DifferenceController;
using ::exception::NotImplementedException;
using ::model::filter::FilteredVideo;

namespace view {

MainControlWidget::MainControlWidget(FilterController::sptr filterController,
	QWidget *parent) : QWidget(parent){
	insertionWidget = new FilterInsertionWidget(filterController, this);
	playerFunctions = new PlayerFunctions(this);
	listView = new FilterListView(filterController, this);

	setupUi(ViewType::PROCESSING_VIEW);
}

MainControlWidget::MainControlWidget(SaveableList<FrameDiff>::sptr differences, Player::sptr player, AnalysingOrderingWidget::sptr orderingWidget,
	QWidget *parent) : QWidget(parent) {
	DifferenceController::sptr differenceController = DifferenceController::sptr(new DifferenceController(differences));
	insertionWidget = new DifferenceInsertionWidget(differenceController, orderingWidget, this);
	playerFunctions = new PlayerFunctions(this);
	listView = new DifferenceListView(differences, differenceController, player, this);
	timeline = new DifferenceTimeline(differences, player, this);

	setupUi(ViewType::ANALYSING_VIEW);

	setPlayer(player);
}

void MainControlWidget::setupUi(ViewType viewType) {
	setAccessibleName("MainControlWidget");
	QWidget *leftWidget = new QWidget(this);
	leftWidget->setAccessibleName("MainControlWidget->leftWidget");
	QWidget *rightWidget = new QWidget(this);
	rightWidget->setAccessibleName("MainControlWidget->rightWidget");

	//Setup left side
	QVBoxLayout *leftWidgetLayout = new QVBoxLayout();

	QHBoxLayout *playerFunctionLayout = new QHBoxLayout();
	btnInsert = new QPushButton(leftWidget);
	btnInsert->setAccessibleName("MainControlWidget->btnInsert");
	btnInsert->setMinimumSize(QSize(30, 30));
	btnInsert->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	if (viewType == ViewType::PROCESSING_VIEW) {
		QString insertFilterIconPath = "Resources/Icons/filter.png";
		if (!QImageReader::imageFormat(insertFilterIconPath).isEmpty()) {
			btnInsert->setMaximumSize(btnInsert->minimumSize());
			btnInsert->setIcon(QIcon(insertFilterIconPath));
			btnInsert->setIconSize(btnInsert->size() * 0.60);
		}
		else {
			btnInsert->setText(tr("INSERT_FILTER"));
		}
		btnInsert->setToolTip(tr("INSERT_FILTER"));

		btnInsert->setEnabled(false);
	} else if (viewType == ViewType::ANALYSING_VIEW) {
		QString insertGraphIconPath = "Resources/Icons/graph.png";
		if (!QImageReader::imageFormat(insertGraphIconPath).isEmpty()) {
			btnInsert->setMaximumSize(btnInsert->minimumSize());
			btnInsert->setIcon(QIcon(insertGraphIconPath));
			btnInsert->setIconSize(btnInsert->size() * 0.60);
		}
		else {
			btnInsert->setText(tr("INSERT_DIFFERENCE"));
		}
		btnInsert->setToolTip(tr("INSERT_DIFFERENCE"));

		btnInsert->setEnabled(true);
	}
	btnInsert->setCheckable(true);
	QObject::connect(btnInsert, SIGNAL(clicked(bool)), this, SLOT(btnInsertClicked(bool)));
	playerFunctionLayout->addWidget(btnInsert);

	QFrame *vLine = new QFrame();
	vLine->setAccessibleName("MainControlWidget->vLine");
	vLine->setFrameShape(QFrame::VLine);
	vLine->setFrameShadow(QFrame::Sunken);
	playerFunctionLayout->addWidget(vLine);

	playerFunctionLayout->addWidget(playerFunctions);

	leftWidgetLayout->addLayout(playerFunctionLayout);
	leftWidgetLayout->addWidget(listView);
	leftWidget->setLayout(leftWidgetLayout);

	//Setup right side
	QVBoxLayout *rightWidgetLayout = new QVBoxLayout();
	rightWidgetLayout->addWidget(playerFunctions->getFrameSlider());

	rightDisplayWidgetLayout = new QStackedLayout();
	if (viewType == ViewType::PROCESSING_VIEW) {
		//TODO Noch die FilterTimeline einbauen
		rightDisplayWidgetLayout->addWidget(new QWidget());
	}
	else if (viewType == ViewType::ANALYSING_VIEW) {
		rightDisplayWidgetLayout->addWidget(timeline);
	}

	QScrollArea *insertionScrollArea = new QScrollArea();
	insertionScrollArea->setAccessibleName("MainControlWidget->insertionScrollArea");
	insertionScrollArea->setWidget(insertionWidget);
	insertionScrollArea->setWidgetResizable(true);

	rightDisplayWidgetLayout->addWidget(insertionScrollArea);
	rightWidgetLayout->addLayout(rightDisplayWidgetLayout);

	rightDisplayWidgetLayout->setCurrentIndex(0);
	rightWidget->setLayout(rightWidgetLayout);

	QSplitter *splitter = new QSplitter(this);
	splitter->setAccessibleName("MainControlWidget->splitter");
	splitter->addWidget(leftWidget);
	splitter->addWidget(rightWidget);

	QHBoxLayout *layout = new QHBoxLayout();
	layout->addWidget(splitter);

	setLayout(layout);
	setMinimumHeight(200);
}

void MainControlWidget::btnInsertClicked(bool active) {
	if (active) {
		rightDisplayWidgetLayout->setCurrentIndex(1);
	} else {
		rightDisplayWidgetLayout->setCurrentIndex(0);
	}
}

void MainControlWidget::setPlayer(Player::sptr player) {
	playerFunctions->setPlayer(player);
}

void MainControlWidget::setVideo(FilteredVideo::sptr video) {
	listView->setVideo(video);
	btnInsert->setEnabled(true);
}

void MainControlWidget::removePlayer() {
	playerFunctions->removePlayer();
}

void MainControlWidget::removeVideo() {
	listView->removeVideo();
	btnInsert->setEnabled(false);
}

void MainControlWidget::update() {
	throw NotImplementedException();
}

}  // namespace view