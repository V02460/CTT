#include "AnalysingOrderingWidget.h"

#include <QSpacerItem>

#include "VideoScrubber.h"
#include "OverlayController.h"
#include "VideoAnalysingWidget.h"


using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::player::VideoScrubber;
using ::controller::OverlayController;

namespace view {
AnalysingOrderingWidget::AnalysingOrderingWidget(SaveableList<FilteredVideo>::sptr filteredVideos,
                                                 Player::sptr player,
                                                 ThumbnailListWidget::sptr thumbnails,
                                                 QWidget *parent)
        : QWidget(parent)
        , filteredVideos(filteredVideos)
        , player(player)
        , thumbnails(thumbnails)
        , activeDialogButtonIds()
        , selectableDialogButtons(0) {
    filteredVideos->subscribe(this);
    setupDialog();
    update();
}

AnalysingOrderingWidget::~AnalysingOrderingWidget() {
	filteredVideos->unsubscribe(this);
}

void AnalysingOrderingWidget::update() {
	QList<int> activatedButtons = thumbnails->getActiveIndices();

	for (int i = 0; i < activatedButtons.size(); i++) {
		int id = activatedButtons[i];
		player->removeScrubber(*analysingWidget.at(id)->getVideoScrubber());
		player->removeScrubber(*analysingWidget.at(id)->getHistogramScrubber());

		widgetLayout->removeWidget(analysingWidget.at(id).data());
		analysingWidget.at(id)->setParent(0);
		dialogLayout->removeWidget(dialogButtons.at(i).data());
		dialogButtons.at(id)->setParent(0);
	}

    for (int i = 0; i < analysingWidget.size(); i++) {
        analysingWidget.at(i)->comboboxOverlayCurrentIndexChanged(0);
        QObject::disconnect(dialogButtons.at(i).data(), SIGNAL(toggled(bool, int)), this, SLOT(dialogButtonToggled(bool, int)));
    }

    analysingWidget.clear();
    dialogButtons.clear();

    for (int i = 0; i < filteredVideos->getSize(); i++) {
        VideoScrubber::sptr scrubber(new VideoScrubber(filteredVideos->get(i)));
		VideoScrubber::sptr histogramScrubber(new VideoScrubber(filteredVideos->get(i)->getBaseVideo()));
        OverlayController::sptr overlayController(new OverlayController(filteredVideos->get(i)));
		VideoAnalysingWidget::sptr widget(new VideoAnalysingWidget(overlayController, scrubber, histogramScrubber, this));
        analysingWidget.insert(i, widget);

        ListedPushButton::sptr dialogButton(new ListedPushButton(i, filteredVideos->get(i)));
        dialogButtons.insert(i, dialogButton);
        QObject::connect(dialogButton.data(), SIGNAL(toggled(bool, int)), this, SLOT(dialogButtonToggled(bool, int)));
    }

    setupUi();
}

void AnalysingOrderingWidget::setupDialog() {
    videoSelectionDialog = new QDialog(this, Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    dialogButtonBox = new QDialogButtonBox(QDialogButtonBox::Cancel, videoSelectionDialog);
    dialogAcceptButton = dialogButtonBox->addButton(QDialogButtonBox::Ok);
	QObject::connect(dialogButtonBox, SIGNAL(accepted()), videoSelectionDialog, SLOT(accept()));
	QObject::connect(dialogButtonBox, SIGNAL(rejected()), videoSelectionDialog, SLOT(reject()));
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
		player->addScrubber(analysingWidget.at(id)->getVideoScrubber());
		player->addScrubber(analysingWidget.at(id)->getHistogramScrubber());
        dialogLayout->addWidget(dialogButtons.at(id).data(), row, column);
    }

    dialogLayout->addWidget(dialogButtonBox, columnCount + 1, 0);
    videoSelectionDialog->setLayout(dialogLayout.data());
    setLayout(widgetLayout.data());
}

QList<FilteredVideo::sptr> AnalysingOrderingWidget::getVideos(int selectableCount) {
    activeDialogButtonIds.clear();
    QList<FilteredVideo::sptr> selectedVideoList = QList<FilteredVideo::sptr>();
    int maxSize = thumbnails->getSelectableCount();

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

	for each (int id in activeDialogButtonIds) {
		dialogButtons.at(id)->setChecked(false);
	}

    return selectedVideoList;
}

void AnalysingOrderingWidget::videoActivated(int id) {
    setupUi();
}

void AnalysingOrderingWidget::videoReplaced(int oldId, int newId) {
	videoDeactivated(oldId);
}

void AnalysingOrderingWidget::videoDeactivated(int id) {
	widgetLayout->removeWidget(analysingWidget.at(id).data());
	analysingWidget.at(id)->setParent(0);
	dialogLayout->removeWidget(dialogButtons.at(id).data());
	dialogButtons.at(id)->setParent(0);
	setupUi();
}

void AnalysingOrderingWidget::dialogButtonToggled(bool checked, int id) {
    if (selectableDialogButtons > 0) {
        if (checked && !activeDialogButtonIds.contains(id)) {
            if (activeDialogButtonIds.size() == selectableDialogButtons) {
				dialogButtons.at(activeDialogButtonIds.first())->setChecked(false);
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
    } else {
        dialogButtons.at(id)->setChecked(false);
    }
}

}  // namespace view