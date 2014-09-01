#include "DifferenceListViewItem.h"

#include <QLabel>

using ::model::difference::FrameDiff;
using ::model::player::Player;

namespace view {
	DifferenceListViewItem::DifferenceListViewItem(FrameDiff::sptr diff, Player::sptr player, QWidget *parent) : AbstractListViewItem(parent), diff(diff), player(player), initialized(false) {
		if (!player.isNull()) {
			player->subscribe(this);
		}

		update();
	}

	QString DifferenceListViewItem::getIdentifier() const {
		return diff->getName();
	}

	void DifferenceListViewItem::update() {
		clear();

		unsigned int currentFrame = player->getCurrentFrameNumber();
		if (!initialized || currentFrame % 25 == 0) {

			if (diff->getFrameCount() < currentFrame) {
				currentFrame = static_cast<double>(diff->getFrameCount()) * 0.1;
			}

			QImage video1Image = diff->getVideo1()->getFrame(currentFrame)->getFramebufferObject()->toImage();
			QImage video2Image = diff->getVideo2()->getFrame(currentFrame)->getFramebufferObject()->toImage();

			QLabel *video1Label = new QLabel(this);
			video1Label->setPixmap(QPixmap::fromImage(video1Image));
			setCellWidget(0, 0, video1Label);

			QLabel *video2Label = new QLabel(this);
			video2Label->setPixmap(QPixmap::fromImage(video2Image));
			setCellWidget(0, 1, video2Label);
		}
	}
}