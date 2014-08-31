#include "DifferenceInsertionWidget.h"

#include "DifferenceFactory.h"

using ::controller::DifferenceController;
using ::model::difference::DifferenceFactory;

namespace view {
	DifferenceInsertionWidget::DifferenceInsertionWidget(DifferenceController::sptr differenceController,
		AnalysingOrderingWidget::sptr orderingWidget, QWidget *parent) : InsertionWidget(parent),
		differenceController(differenceController), orderingWidget(orderingWidget) {
		generateButtons();
		setupUi();
		//TODO Connect an DifferenceController
	}

	void DifferenceInsertionWidget::generateButtons() {
		QList<QString> diffIds = DifferenceFactory::getAllFrameDiffIDs();
		for (int i = 0; i < diffIds.size(); i++) {
			ListedPushButton *button = new ListedPushButton(i, this);
			button->setText(diffIds.at(i));
			button->setMinimumSize(preferredButtonSize);
			button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			insertionButtons.append(button);
			QObject::connect(button, SIGNAL(clicked(bool, int)), this, SLOT(listedButtonClicked(bool, int)));
		}
	}
	
	void DifferenceInsertionWidget::listedPushButtonClicked(bool checked, int id) {

	}
}