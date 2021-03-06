#include "ListedPushButton.h"

#include <QApplication>
#include <QMenu>

using ::model::filter::FilteredVideo;

namespace view {

	ListedPushButton::ListedPushButton(int id,
									   FilteredVideo::sptr video,
									   QWidget *parent) : QToolButton(parent),
									                      video(video),
														  id(id) {
		init();
		if (!video.isNull()) {
			video->subscribe(this);
			setThumbnail();
			QString videoIdentifier = video->getIdentifier();
			setToolTip(videoIdentifier);
			if (videoIdentifier.size() > 25) {
				videoIdentifier.resize(25);
				videoIdentifier.append("...");
			}
			setText(videoIdentifier);
		} else {
			setText(tr("NO_VIDEO_SPECIFIED"));
		}

		QSizePolicy sizePolicy = QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
		setSizePolicy(sizePolicy);
		setMinimumSize(ListedPushButton::MINIMUM_SIZE);
		setCheckable(true);
		// TODO setFlat(true);

		QMenu *buttonMenu = new QMenu(this);
		QObject::connect(buttonMenu->addAction(tr("REMOVE")), SIGNAL(triggered(bool)), this, SLOT(removeToggled(bool)));
		setMenu(buttonMenu);
		setPopupMode(QToolButton::MenuButtonPopup);
	}

	ListedPushButton::~ListedPushButton() {
		if (!video.isNull()) {
			video->unsubscribe(this);
		}
	}

	ListedPushButton::ListedPushButton(int id, QWidget *parent) : QToolButton(parent), id(id) {
		init();
	}

	void ListedPushButton::init() {
		setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
		QObject::connect(this, SIGNAL(toggled(bool)), this, SLOT(buttonToggled(bool)));
		QObject::connect(this, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
	}

	void ListedPushButton::update() {
		setThumbnail();
	}

	void ListedPushButton::setIndex(int index) {
		id = index;
	}

	int ListedPushButton::getIndex() {
		return id;
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

	FilteredVideo::sptr ListedPushButton::getVideo() {
		return video;
	}

	void ListedPushButton::resizeEvent(QResizeEvent *ev) {
		Q_UNUSED(ev);

		double buttonRatio = (double) width() / height();
		int border = 20;

		if (buttonRatio >= iconRatio) {
			setIconSize(QSize((height() - border) * iconRatio, height() - border));
		} else {
			setIconSize(QSize(width() - border, (width() - border) * (1 / iconRatio)));
		}
	}

	const QSize ListedPushButton::MINIMUM_SIZE = QSize(160, 90);

} // namespace view