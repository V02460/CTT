#ifndef _THUMBNAILLISTWIDGETTEST
#define _THUMBNAILLISTWIDGETTEST

#include "ThumbnailListWidget.h"
#include <QWidget>
#include <QLabel>

class ThumbnailListWidgetTest : public QWidget {
	Q_OBJECT
public:
	ThumbnailListWidgetTest(QWidget *parent = 0);

private:
	void setupUi();

	view::ThumbnailListWidget *horizontal;
	view::ThumbnailListWidget *vertical;

	QLabel *lblhorizontalActivated;
	QLabel *lblhorizontalDeactivated;
	QLabel *lblverticalActivated;
	QLabel *lblverticalDeactivated;

	QLabel *lblhorizontalVideoAdded;
	QLabel *lblverticalVideoAdded;

private slots:
	void horizontalActivated(int id);
	void horizontalDeactivated(int id);
	void horizontalReplaced(int oldId, int newId);
	void verticalActivated(int id);
	void verticalDeactivated(int id);
	void verticalReplaced(int oldId, int newId);
	void horizontalVideoAdded(QString path);
	void verticalVideoAdded(QString path);
};

#endif //_THUMBNAILLISTWIDGETTEST