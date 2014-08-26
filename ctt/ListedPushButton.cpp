#include "ListedPushButton.h"

#include <QApplication>
#include <QMenu>

namespace view {
	ListedPushButton::ListedPushButton(int id, model::filter::FilteredVideo::sptr video, QWidget *parent) : QToolButton(parent) {
		init(id);
		
		this->video = video;
		if (video.data() != 0) {
			video->subscribe(ListedPushButton::sptr(this));

			setThumbnail();
		} else {
			setText(tr("NO_VIDEO_SPECIFIED") + " ID: " + QString::number(id));
		}

		QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
		setSizePolicy(sizePolicy);
		setMinimumSize(QSize(80, 45));
		setCheckable(true);
		//setFlat(true);

		QMenu *buttonMenu = new QMenu();
		QAction* removeAction = buttonMenu->addAction("Entfernen");
		QObject::connect(removeAction, SIGNAL(toggled(bool)), this, SLOT(removeToggled(bool)));

		setMenu(buttonMenu);
		setPopupMode(QToolButton::MenuButtonPopup);
	}

	ListedPushButton::ListedPushButton(int id, QWidget *parent) : QToolButton(parent) {
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
		int thumbnailFrame = video->getFrameCount() * 0.09;
		QImage iconImage = video->getFrame(thumbnailFrame)->getFramebufferObject()->toImage();
		iconRatio = (double) iconImage.width() / iconImage.height();
		setIcon(QIcon(QPixmap::fromImage(iconImage)));
	}

	void ListedPushButton::buttonClicked(bool checked) {
		emit clicked(checked, id);
	}

	void ListedPushButton::buttonToggled(bool checked) {
		emit toggled(checked, id);
	}

	void ListedPushButton::removeToggled(bool checked) {
		emit removed(checked, id);
	}

	void ListedPushButton::resizeEvent(QResizeEvent *ev) {
		Q_UNUSED(ev);

		double buttonRatio = (double) width() / height();
		int border = 10;

		if (buttonRatio >= iconRatio) {
			setIconSize(QSize((height() - border) * iconRatio, height() - border));
		} else {
			setIconSize(QSize(width() - border, (width() - border) * (1 / iconRatio)));
		}
	}

} // namespace view