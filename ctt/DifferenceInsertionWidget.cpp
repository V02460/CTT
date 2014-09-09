#include "DifferenceInsertionWidget.h"

#include <QMessageBox>

#include "DifferenceFactory.h"

using ::controller::DifferenceController;
using ::model::difference::DifferenceFactory;
using ::model::filter::FilteredVideo;
using ::model::video::Video;

namespace view {
	DifferenceInsertionWidget::DifferenceInsertionWidget(DifferenceController::sptr differenceController,
		AnalysingOrderingWidget::sptr orderingWidget, QWidget *parent) : InsertionWidget(parent),
		differenceController(differenceController), orderingWidget(orderingWidget) {
		generateButtons();
		setupUi();
		QObject::connect(this, SIGNAL(inserted(QString, ::model::video::Video::sptr, ::model::video::Video::sptr)),
			differenceController.data(), SLOT(diffInserted(QString, ::model::video::Video::sptr, ::model::video::Video::sptr)));
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
	
	void DifferenceInsertionWidget::listedButtonClicked(bool checked, int id) {
		QList<FilteredVideo::sptr> selectedVideos = orderingWidget->getVideos(2);

		if (selectedVideos.size() == 2) {
			emit inserted(DifferenceFactory::getAllFrameDiffIDs().at(id), selectedVideos.value(0).dynamicCast<Video>(), selectedVideos.value(1).dynamicCast<Video>());
		} else if(selectedVideos.size() != 0) {
			QMessageBox::warning(this, tr("DIFFERENCE_INSERTION_FAILED_TITLE"), tr("DIFFERENCE_INSERTION_FAILED"));
		}
	}
}