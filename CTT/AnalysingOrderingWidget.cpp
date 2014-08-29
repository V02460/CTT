#include "AnalysingOrderingWidget.h"

using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;

namespace view {
	AnalysingOrderingWidget::AnalysingOrderingWidget(SaveableList<FilteredVideo>::sptr filteredVideos,
		Player::sptr player, ThumbnailListWidget::sptr thumbnails, QWidget *parent) : QWidget(parent), filteredVideos(filteredVideos),
		player(player), thumbnails(thumbnails) {
		update();
	}

	void AnalysingOrderingWidget::update() {

	}

	void AnalysingOrderingWidget::videoActivated(int id) {

	}

	void AnalysingOrderingWidget::videoReplaced(int oldId, int newId) {

	}

	void AnalysingOrderingWidget::videoDeactivated(int id) {

	}
}