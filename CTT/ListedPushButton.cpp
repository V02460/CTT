#include "ListedPushButton.h"

namespace view {
	ListedPushButton::ListedPushButton(int id, model::video::Video::sptr video, QWidget *parent) : QPushButton(parent) {
		init(id);
		
		this->video = video;
		video->subscribe(ListedPushButton::sptr(this));

		setThumbnail();
	}

	ListedPushButton::ListedPushButton(int id, QWidget *parent) : QPushButton(parent) {
		init(id);
	}

	void ListedPushButton::init(int id) {
		connect(this, SIGNAL(toggled(bool)), this, SLOT(buttonToggled(bool)));
		connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));

		this->id = id;
	}

	void ListedPushButton::update() {
		setThumbnail();
	}

	void ListedPushButton::setThumbnail() {
		setIcon(QIcon(QPixmap::fromImage(video->getFrame(12)->getFramebufferObject()->toImage())));
		setIconSize(size());
		setFlat(true);
		setCheckable(true);
	}

	void ListedPushButton::buttonClicked(bool checked) {
		emit clicked(checked, id);
	}

	void ListedPushButton::buttonToggled(bool checked) {
		emit toggled(checked, id);
	}

} // namespace view