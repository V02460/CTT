#include "ListedPushButtonTest.h"

#include <QGridLayout>
#include <QOffscreenSurface>

ListedPushButtonTest::ListedPushButtonTest(QWidget *parent) : QWidget(parent) {
	count = 0;
	setupUi();
}

void ListedPushButtonTest::setupUi() {
	lpbOne = new view::ListedPushButton(0, model::filter::FilteredVideo::sptr(), this);
	lpbTwo = new view::ListedPushButton(1, model::filter::FilteredVideo::sptr(), this);
	//lpbOne->setCheckable(true);
	//lpbTwo->setCheckable(true);

	QGridLayout *testLayout = new QGridLayout(this);
	testLayout->addWidget(lpbOne, 0, 0);
	testLayout->addWidget(lpbTwo, 1, 0);

	clickedOne = new QLabel("Click One", this);
	clickedTwo = new QLabel("Click Two", this);
	testLayout->addWidget(clickedOne, 0, 1);
	testLayout->addWidget(clickedTwo, 1, 1);
	QObject::connect(lpbOne, SIGNAL(clicked(bool, int)), this, SLOT(buttonClicked(bool, int)));
	QObject::connect(lpbTwo, SIGNAL(clicked(bool, int)), this, SLOT(buttonClicked(bool, int)));

	toggledOne = new QLabel("Toggle One", this);
	toggledTwo = new QLabel("Toggle Two", this);
	testLayout->addWidget(toggledOne, 0, 2);
	testLayout->addWidget(toggledTwo, 1, 2);
	QObject::connect(lpbOne, SIGNAL(toggled(bool, int)), this, SLOT(buttonToggled(bool, int)));
	QObject::connect(lpbTwo, SIGNAL(toggled(bool, int)), this, SLOT(buttonToggled(bool, int)));

	setWindowTitle("ListedPushButtonTest");
}

void ListedPushButtonTest::buttonClicked(bool checked, int id) {
	if (id == 0) {
		clickedOne->setText("Clicked One" );
	}
	else if (id == 1) {
		clickedTwo->setText("Clicked Two");
	}
}

void ListedPushButtonTest::buttonToggled(bool checked, int id) {
	if (id == 0) {
		if (checked) {
			toggledOne->setText("Checked One");
		}
		else {
			toggledOne->setText("Unchecked One");
		}
		
	}
	else if (id == 1) {
		if (checked) {
			toggledTwo->setText("Checked Two");
		}
		else {
			toggledTwo->setText("Unchecked Two");
		}
	}
}