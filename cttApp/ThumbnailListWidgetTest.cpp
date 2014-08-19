#include "ThumbnailListWidgetTest.h"
#include <QLayout>
#include <QScrollArea>

ThumbnailListWidgetTest::ThumbnailListWidgetTest(QWidget *parent) : QWidget(parent) {
	horizontal = new view::ThumbnailListWidget(model::saveable::SaveableList<model::filter::FilteredVideo>::sptr(), 4, true, this);
	vertical = new view::ThumbnailListWidget(model::saveable::SaveableList<model::filter::FilteredVideo>::sptr(), 4, false, this);

	QObject::connect(horizontal, SIGNAL(buttonActivated(int)), this, SLOT(horizontalActivated(int)));
	QObject::connect(vertical, SIGNAL(buttonActivated(int)), this, SLOT(verticalActivated(int)));
	QObject::connect(horizontal, SIGNAL(buttonDeactivated(int)), this, SLOT(horizontalDeactivated(int)));
	QObject::connect(vertical, SIGNAL(buttonDeactivated(int)), this, SLOT(verticalDeactivated(int)));
	QObject::connect(horizontal, SIGNAL(buttonReplaced(int, int)), this, SLOT(horizontalReplaced(int, int)));
	QObject::connect(vertical, SIGNAL(buttonReplaced(int, int)), this, SLOT(verticalReplaced(int, int)));

	QObject::connect(horizontal, SIGNAL(videoAdded(QString)), this, SLOT(horizontalVideoAdded(QString)));
	QObject::connect(vertical, SIGNAL(videoAdded(QString)), this, SLOT(verticalVideoAdded(QString)));

	setupUi();
}

void ThumbnailListWidgetTest::setupUi() {
	QGridLayout *layout = new QGridLayout(this);
	
	QScrollArea *horizontalScrollArea = new QScrollArea(this);
	horizontalScrollArea->setWidget(horizontal);
	horizontalScrollArea->setWidgetResizable(true);
	QScrollArea *verticalScrollArea = new QScrollArea(this);
	verticalScrollArea->setWidget(vertical);
	verticalScrollArea->setWidgetResizable(true);
	layout->addWidget(horizontalScrollArea, 0, 1, 1, 3);
	layout->addWidget(verticalScrollArea, 1, 0, 3, 1);

	lblhorizontalActivated = new QLabel("Horizontal activated");
	lblverticalActivated = new QLabel("Vertical activated");
	layout->addWidget(lblhorizontalActivated, 1, 1);
	layout->addWidget(lblverticalActivated, 1, 2);

	lblhorizontalDeactivated = new QLabel("Horizontal deactivated");
	lblverticalDeactivated = new QLabel("Vertical deactivated");
	layout->addWidget(lblhorizontalDeactivated, 2, 1);
	layout->addWidget(lblverticalDeactivated, 2, 2);

	lblhorizontalVideoAdded = new QLabel("Horizontal video added");
	lblverticalVideoAdded = new QLabel("Vertical video added");
	layout->addWidget(lblhorizontalVideoAdded, 3, 1);
	layout->addWidget(lblverticalVideoAdded, 3, 2);

	setLayout(layout);
}

void ThumbnailListWidgetTest::horizontalActivated(int id) {
	lblhorizontalActivated->setText("Horizontal activated; ID: " + QString::number(id));
}

void ThumbnailListWidgetTest::verticalActivated(int id) {
	lblverticalActivated->setText("Vertical activated; ID: " + QString::number(id));
}

void ThumbnailListWidgetTest::horizontalDeactivated(int id) {
	lblhorizontalDeactivated->setText("Horizontal deactivated; ID: " + QString::number(id));
}

void ThumbnailListWidgetTest::verticalDeactivated(int id) {
	lblverticalDeactivated->setText("Vertical deactivated; ID: " + QString::number(id));
}

void ThumbnailListWidgetTest::horizontalReplaced(int oldId, int newId) {
	horizontalActivated(newId);
	horizontalDeactivated(oldId);
}

void ThumbnailListWidgetTest::verticalReplaced(int oldId, int newId) {
	verticalActivated(newId);
	verticalDeactivated(oldId);
}

void ThumbnailListWidgetTest::horizontalVideoAdded(QString path) {
	lblhorizontalVideoAdded->setText(path);
}

void ThumbnailListWidgetTest::verticalVideoAdded(QString path) {
	lblverticalVideoAdded->setText(path);
}