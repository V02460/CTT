#include "FilterInsertionWidget.h"

#include <QCoreApplication>

#include "FilterFactory.h"
#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

FilterInsertionWidget::FilterInsertionWidget(::controller::FilterController::sptr controller,
	                                         QWidget *parent) : InsertionWidget(parent),
											                    filterController(controller) {
	generateButtons();
	// TODO rearrangeContents();
	setupUi();
	QObject::connect(this, SIGNAL(inserted(QString)), controller.data(), SLOT(insertFilter(QString)));
}

void FilterInsertionWidget::generateButtons() {
    QList<QByteArray> filterIds = model::filter::FilterFactory::getAllNonOverlayFilterIDs();
	for (int i = 0; i < filterIds.size(); i++) {
		ListedPushButton *button = new ListedPushButton(i, this);
        button->setText(QCoreApplication::translate("Filter", filterIds.at(i)));
		button->setMinimumSize(preferredButtonSize);
		button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
		insertionButtons.append(button);
		QObject::connect(button, SIGNAL(clicked(bool, int)), this, SLOT(listedButtonClicked(bool, int)));
	}
}

void FilterInsertionWidget::listedButtonClicked(bool checked, int id) {
	QString filterId = model::filter::FilterFactory::getAllNonOverlayFilterIDs()[id];
	emit inserted(filterId);
}

} // namespace view