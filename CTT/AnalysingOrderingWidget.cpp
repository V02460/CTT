#include "AnalysingOrderingWidget.h"

#include "VideoScrubber.h"
#include "OverlayController.h"

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::player::VideoScrubber;
using ::controller::OverlayController;

namespace view {
	AnalysingOrderingWidget::AnalysingOrderingWidget(SaveableList<FilteredVideo>::sptr filteredVideos,
		Player::sptr player, ThumbnailListWidget::sptr thumbnails, QWidget *parent) : QWidget(parent), filteredVideos(filteredVideos),
		player(player), thumbnails(thumbnails), activeDialogButtonIds(), selectableDialogButtons(0) {
		filteredVideos->subscribe(this);
		setupDialog();
		update();
	}

	void AnalysingOrderingWidget::update() {
		widgetLayout.reset(new QGridLayout(this));
		dialogLayout.reset(new QGridLayout(videoSelectionDialog));

		for (int i = 0; i < analysingWidget.size(); i++) {
			analysingWidget.at(i)->comboboxOverlayCurrentIndexChanged(0);
			QObject::disconnect(dialogButtons.at(i).data(), SIGNAL(toggled(bool, int)), this, SLOT(dialogButtonToggled(bool, int)));
		}

		analysingWidget.clear();
		dialogButtons.clear();

		for (int i = 0; i < filteredVideos->getSize(); i++) {
			VideoScrubber::sptr scrubber(new VideoScrubber(filteredVideos->get(i)));
			OverlayController::sptr overlayController(new OverlayController(filteredVideos->get(i)));
			analysingWidget.insert(i, VideoAnalysingWidget::sptr(new VideoAnalysingWidget(overlayController, scrubber)));

			ListedPushButton::sptr dialogButton(new ListedPushButton(i, filteredVideos->get(i), videoSelectionDialog));
			dialogButtons.insert(i, dialogButton);
			QObject::connect(dialogButton.data(), SIGNAL(toggled(bool, int)), this, SLOT(dialogButtonToggled(bool, int)));
		}
	}

	void AnalysingOrderingWidget::setupDialog() {
		videoSelectionDialog = new QDialog(this, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

		dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, videoSelectionDialog);
		dialogAcceptButton = dialogButtonBox->addButton(QDialogButtonBox::Ok);
		dialogAcceptButton->setEnabled(false);
	}

	void AnalysingOrderingWidget::setupUi() {
		widgetLayout.reset(new QGridLayout());
		dialogLayout.reset(new QGridLayout());

		int columnCount = static_cast<int>(ceil(sqrt(thumbnails->getSelectableCount())));

		QList<int> activatedButtons = thumbnails->getActiveIndices();

		for (int i = 0; i < activatedButtons.size(); i++) {
			int row = i / columnCount;
			int column = i % columnCount;
			int id = activatedButtons.at(i);

			widgetLayout->addWidget(analysingWidget.at(id).data(), row, column);
			dialogLayout->addWidget(dialogButtons.at(id).data(), row, column);
		}

		dialogLayout->addWidget(dialogButtonBox, columnCount + 1, 0);
	}

	QList<FilteredVideo::sptr> AnalysingOrderingWidget::getVideos(int selectableCount) {
		activeDialogButtonIds.clear();
		QList<FilteredVideo::sptr> selectedVideoList = QList<FilteredVideo::sptr>();
		int maxSize = thumbnails->getActiveIndices().size();

		if (selectableCount <= maxSize && selectableCount > 0) {
			selectableDialogButtons = selectableCount;
		} else {
			selectableDialogButtons = maxSize;
		}

		videoSelectionDialog->setWindowTitle(selectableCount + " " + tr("VIDEOS_TO_SELECT"));

		if (videoSelectionDialog->exec() == QDialog::Accepted) {
			for each (int id in activeDialogButtonIds) {
				selectedVideoList.append(filteredVideos->get(id));
			}
		}

		return selectedVideoList;
	}

	void AnalysingOrderingWidget::videoActivated(int id) {
		setupUi();
	}

	void AnalysingOrderingWidget::videoReplaced(int oldId, int newId) {
		setupUi();
	}

	void AnalysingOrderingWidget::videoDeactivated(int id) {
		setupUi();
	}

	void AnalysingOrderingWidget::dialogButtonToggled(bool checked, int id) {
		if (checked && !activeDialogButtonIds.contains(id)) {
			if (activeDialogButtonIds.size() == selectableDialogButtons) {
				activeDialogButtonIds.removeFirst();
			}
			
			activeDialogButtonIds.append(id);

			if (activeDialogButtonIds.size() == selectableDialogButtons) {
				dialogAcceptButton->setEnabled(true);
			}
		} else if (!checked && activeDialogButtonIds.contains(id)) {
			activeDialogButtonIds.removeOne(id);

			dialogAcceptButton->setEnabled(false);
		}
	}
}