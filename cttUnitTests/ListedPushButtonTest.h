#ifndef _LISTEDPUSHBUTTONTEST
#define _LISTEDPUSHBUTTONTEST

#include <QWidget>
#include <QLabel>

#include "ListedPushButton.h"

class ListedPushButtonTest : public QWidget {
	Q_OBJECT
public:
	ListedPushButtonTest(QWidget *parent = 0);
private slots:
	void buttonClicked(bool checked, int id);
	void buttonToggled(bool checked, int id);
private:
	void setupUi();

	view::ListedPushButton *lpbOne;
	view::ListedPushButton *lpbTwo;
	QLabel *clickedOne;
	QLabel *clickedTwo;
	QLabel *toggledOne;
	QLabel *toggledTwo;

	int count;

};

#endif //_LISTEDPUSHBUTTONTEST