#include "InsertionWidget.h"

namespace view {

InsertionWidget::InsertionWidget(QWidget *parent) : QWidget(parent) {
	insertionButtons = QList<ListedPushButton::sptr>();
	spacers = QList<QSpacerItem*>();
	preferredButtonSize = QSize(100, 50);

	setupUi();
}

void InsertionWidget::setupUi() {
	setAccessibleName("InsertionWidget");
	layout = new QGridLayout();

	setLayout(layout);

	rearrangeContents();
}

void InsertionWidget::rearrangeContents() {
	removeContents();

	QSize widgetSize = size();

	int maxColumnCount = widgetSize.width() / (preferredButtonSize.width() + layout->spacing());
	int columnCount = 0;
	int rowCount = 0;
	
	for each (ListedPushButton::sptr button in insertionButtons) {
		if (columnCount == maxColumnCount) {
			QSpacerItem *rowSpacer = new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
			layout->addItem(rowSpacer, rowCount, columnCount);
			spacers.append(rowSpacer);

			columnCount = 0;
			rowCount++;	
		}

		layout->addWidget(button.data(), rowCount, columnCount);
		columnCount++;
	}

	int j = columnCount;
	for (int i = 0; i < maxColumnCount; i++) {
		if (j == maxColumnCount) {
			j = 0;
			rowCount++;
		}

		QSpacerItem *columnSpacer = new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);
		layout->addItem(columnSpacer, rowCount, j);
		spacers.append(columnSpacer);
		j++;
	}
}

void InsertionWidget::removeContents() {
	for each (ListedPushButton::sptr button in insertionButtons) {
		layout->removeWidget(button.data());
	}

	for each (QSpacerItem *spacer in spacers) {
		layout->removeItem(spacer);
		spacers.removeOne(spacer);
		delete spacer;
	}
}

void InsertionWidget::resizeEvent(QResizeEvent *ev) {
	Q_UNUSED(ev);

	rearrangeContents();
}

}  // namespace view