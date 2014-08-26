#include "MainControlWidget.h"

#include <QLayout>
#include <QFrame>
#include <QScrollArea>
#include <QSplitter>
#include "FilterInsertionWidget.h"
#include "FilterListView.h"

using ::controller::FilterController;
using ::controller::DifferenceController;
using ::model::player::Player;

namespace view {

MainControlWidget::MainControlWidget(FilterController::sptr filterController,
	QWidget *parent) : QWidget(parent){
	insertionWidget = new FilterInsertionWidget(filterController, this);
	playerFunctions = new PlayerFunctions(this);
	listView = new FilterListView(filterController, this);

	setupUi(ViewType::PROCESSING_VIEW);
}

MainControlWidget::MainControlWidget(DifferenceController::sptr filterController,
	QWidget *parent) : QWidget(parent){
	setupUi(ViewType::ANALYSING_VIEW);
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
		btnInsert->setText(tr("INSERT_FILTER"));
	} else if (viewType == ViewType::ANALYSING_VIEW) {
		btnInsert->setText(tr("INSERT_DIFFERENCE"));
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
	leftWidgetLayout->addStretch();
	leftWidget->setLayout(leftWidgetLayout);

	//Setup right side
	QVBoxLayout *rightWidgetLayout = new QVBoxLayout();
	rightWidgetLayout->addWidget(playerFunctions->getFrameSlider());

	rightDisplayWidgetLayout = new QStackedLayout();
	//Platzhalter für die Timelines
	rightDisplayWidgetLayout->addWidget(new QWidget());

	QScrollArea *insertionScrollArea = new QScrollArea();
	insertionScrollArea->setAccessibleName("MainControlWidget->insertionScrollArea");
	insertionScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
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

void MainControlWidget::removePlayer() {

}

}  // namespace view