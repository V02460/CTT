#include "MainControlWidget.h"

#include <QLayout>
#include <QFrame>
#include <QScrollArea>
#include <QSplitter>
#include "FilterInsertionWidget.h"

namespace view {

MainControlWidget::MainControlWidget(::model::player::Player::sptr player, ::controller::FilterController::sptr filterController,
	QWidget *parent) : QWidget(parent){
	insertionWidget = new FilterInsertionWidget(filterController, this);
	playerFunctions = new PlayerFunctions(player, this);

	setupUi(ViewType::PROCESSING_VIEW);
}

MainControlWidget::MainControlWidget(::model::player::Player::sptr player, ::controller::DifferenceController::sptr filterController,
	QWidget *parent) : QWidget(parent){
	setupUi(ViewType::ANALYSING_VIEW);

	setPlayer(player);
}

void MainControlWidget::setupUi(ViewType viewType) {
	QWidget *leftWidget = new QWidget(this);
	QWidget *rightWidget = new QWidget(this);

	//Setup left side
	QVBoxLayout *leftWidgetLayout = new QVBoxLayout(leftWidget);

	QHBoxLayout *playerFunctionLayout = new QHBoxLayout(leftWidget);
	btnInsert = new QPushButton(leftWidget);
	btnInsert->setMinimumSize(QSize(30, 30));
	btnInsert->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	if (viewType == ViewType::PROCESSING_VIEW) {
		btnInsert->setText(tr("INSERT_FILTER"));
	} else if (viewType == ViewType::ANALYSING_VIEW) {
		btnInsert->setText(tr("INSERT_DIFFERENCE"));
	}
	QObject::connect(btnInsert, SIGNAL(clicked(bool)), this, SLOT(btnInsertClicked(bool)));
	playerFunctionLayout->addWidget(btnInsert);

	QFrame *vLine = new QFrame();
	vLine->setFrameShape(QFrame::VLine);
	vLine->setFrameShadow(QFrame::Sunken);
	playerFunctionLayout->addWidget(vLine);

	playerFunctionLayout->addWidget(playerFunctions);

	leftWidgetLayout->addLayout(playerFunctionLayout);
	leftWidgetLayout->addStretch();
	leftWidget->setLayout(leftWidgetLayout);

	//Setup right side
	rightWidgetLayout = new QStackedLayout(rightWidget);

	QWidget *rightDisplayWidget = new QWidget(rightWidget);

	QVBoxLayout *rightDisplayWidgetLayout = new QVBoxLayout(rightDisplayWidget);
	rightDisplayWidgetLayout->addWidget(playerFunctions->getFrameSlider());
	rightDisplayWidgetLayout->addStretch();

	rightDisplayWidget->setLayout(rightDisplayWidgetLayout);
	rightWidgetLayout->addWidget(rightDisplayWidget);

	QScrollArea *insertionScrollArea = new QScrollArea(rightWidget);
	insertionScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	insertionScrollArea->setViewport(insertionWidget);
	insertionScrollArea->setWidgetResizable(true);

	rightWidgetLayout->addWidget(insertionScrollArea);

	rightWidgetLayout->setCurrentIndex(0);
	rightWidget->setLayout(rightWidgetLayout);

	QSplitter *splitter = new QSplitter(this);
	splitter->addWidget(leftWidget);
	splitter->addWidget(rightWidget);

	QHBoxLayout *layout = new QHBoxLayout(this);
	layout->addWidget(splitter);

	setLayout(layout);
}

void MainControlWidget::btnInsertClicked(bool active) {
	if (active) {
		rightWidgetLayout->setCurrentIndex(1);
	} else {
		rightWidgetLayout->setCurrentIndex(0);
	}
}

void MainControlWidget::setPlayer(::model::player::Player::sptr player) {
	playerFunctions->setPlayer(player);
}

}  // namespace view