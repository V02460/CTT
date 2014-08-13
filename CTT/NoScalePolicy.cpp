#include "NoScalePolicy.h"

namespace view {

QRect NoScalePolicy::getViewportSize(QSize windowSize, QSize videoSize) {
	QRect viewportSize = QRect(0, 0, windowSize.width(), windowSize.height());

	if (windowSize.width() > videoSize.width()) {
		viewportSize.setX((windowSize.width() - videoSize.width()) / 2);
		viewportSize.setWidth(videoSize.height());
	}

	if (windowSize.height() > videoSize.height()) {
		viewportSize.setY((windowSize.height() - videoSize.height()) / 2);
		viewportSize.setHeight(videoSize.height());
	}

	return viewportSize;
}

} // namespace view