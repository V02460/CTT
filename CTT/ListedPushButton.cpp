#include "ListedPushButton.h"

#include <QApplication>

namespace view {
	ListedPushButton::ListedPushButton(int id, model::video::Video::sptr video, QWidget *parent) : QPushButton(parent) {
		init(id);
		
		this->video = video;
		if (video.data() != 0) {
			video->subscribe(ListedPushButton::sptr(this));

			setThumbnail();
		} else {
			setText(tr("NO_VIDEO_SPECIFIED") + " ID: " + QString::number(id));
		}

		QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
		sizePolicy.setHeightForWidth(true);
		sizePolicy.setWidthForHeight(true);
		setSizePolicy(sizePolicy);
		setMinimumSize(QSize(160, 90));
		setCheckable(true);
	}

	ListedPushButton::ListedPushButton(int id, QWidget *parent) : QPushButton(parent) {
		init(id);
	}

	void ListedPushButton::init(int id) {
		QObject::connect(this, SIGNAL(toggled(bool)), this, SLOT(buttonToggled(bool)));
		QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));

		this->id = id;
	}

	void ListedPushButton::update() {
		setThumbnail();
	}

	void ListedPushButton::setThumbnail() {
		setIcon(QIcon(QPixmap::fromImage(video->getFrame(12)->getFramebufferObject()->toImage())));
		setIconSize(size());
	}

	void ListedPushButton::buttonClicked(bool checked) {
		emit clicked(checked, id);
	}

	void ListedPushButton::buttonToggled(bool checked) {
		emit toggled(checked, id);
	}

} // namespace view