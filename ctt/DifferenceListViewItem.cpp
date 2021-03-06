#include "DifferenceListViewItem.h"

#include <QLabel>
#include <QPixmap>
#include <QBitmap>
#include <QHeaderView>

using ::model::difference::FrameDiff;
using ::model::player::Player;

namespace view {
	DifferenceListViewItem::DifferenceListViewItem(FrameDiff::sptr diff, Player::sptr player, QColor diffColor, QWidget *parent) : AbstractListViewItem(parent), diff(diff), player(player), initialized(false) {
		if (!player.isNull()) {
			player->subscribe(this);
		}

		identifierLabel = new QLabel(diff->getName());
		QPalette labelPalette = identifierLabel->palette();
		labelPalette.setColor(QPalette::Text, diffColor);
		identifierLabel->setPalette(labelPalette);

		setColumnCount(2);
		setRowCount(1);

		setHeight(100);

		update();
	}

	DifferenceListViewItem::~DifferenceListViewItem() {
		player->unsubscribe(this);
	}

	QLabel* DifferenceListViewItem::getIdentifier() const {
		return identifierLabel;
	}

	void DifferenceListViewItem::update() {
		unsigned int currentFrame = player->getCurrentFrameNumber();
		if (!initialized || currentFrame % 25 == 0) {
			clear();

			if (diff->getFrameCount() < currentFrame) {
				currentFrame = static_cast<double>(diff->getFrameCount()) * 0.1;
			}

			QImage video1Image = diff->getModule1()->getFrame(currentFrame)->getFramebufferObject()->toImage();
			QImage video2Image = diff->getModule2()->getFrame(currentFrame)->getFramebufferObject()->toImage();

			QTableWidgetItem *video1Item = new QTableWidgetItem();
			video1Item->setData(Qt::DecorationRole, QPixmap::fromImage(video1Image).scaledToHeight(getHeight()));
			setItem(0, 0, video1Item);

			QTableWidgetItem *video2Item = new QTableWidgetItem();
			video2Item->setData(Qt::DecorationRole, QPixmap::fromImage(video2Image).scaledToHeight(getHeight()));
			setItem(0, 1, video2Item);

			initialized = true;
		}
	}

	bool DifferenceListViewItem::equals(AbstractListViewItem *abstractOther) {
		DifferenceListViewItem *other = dynamic_cast<DifferenceListViewItem*>(abstractOther);
		if (other == nullptr) { return false; }
		return diff == other->diff;
	}
}