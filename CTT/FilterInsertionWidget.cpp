#include "FilterInsertionWidget.h"

#include "FilterFactory.h"

namespace view {
FilterInsertionWidget::FilterInsertionWidget(::controller::FilterController::sptr controller, QWidget *parent) 
	: InsertionWidget(parent) {
	generateButtons();

	//rearrangeContents();
	setupUi();

	QObject::connect(this, SIGNAL(inserted(QString)), controller.data(), SLOT(insertFilter(QString)));
	this->filterController = controller;
}

void FilterInsertionWidget::generateButtons() {
	QList<QString> filterIds = model::filter::FilterFactory::getAllNonOverlayFilterIDs();

	for (int i = 0; i < filterIds.size(); i++) {
		ListedPushButton::sptr button = ListedPushButton::sptr(new ListedPushButton(i, this));
		button->setText(filterIds.at(i));
		button->setMinimumSize(preferredButtonSize);
		button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		insertionButtons.append(button);

		QObject::connect(button.data(), SIGNAL(clicked(bool, int)), this, SLOT(listedButtonClicked(bool, int)));
	}
}

void FilterInsertionWidget::listedButtonClicked(bool checked, int id) {
	QString filterId = model::filter::FilterFactory::getAllNonOverlayFilterIDs().at(id);

	emit inserted(filterId);
}
} // namespace view