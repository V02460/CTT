#include "AbstractListViewItem.h"

#include <QHeaderView>

namespace view {
	AbstractListViewItem::AbstractListViewItem(QWidget* parent) : QTableWidget(parent), forcedHeight(0) {
		verticalHeader()->setVisible(true);
		horizontalHeader()->setVisible(false);
		horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	}

	void AbstractListViewItem::setHeight(int height) {
		this->forcedHeight = height;
	}

	const int AbstractListViewItem::getHeight() {
		return forcedHeight;
	}
}