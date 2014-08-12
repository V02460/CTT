#ifndef _VIDEODISPLAYPOLICY
#define _VIDEODISPLAYPOLICY

#include <QRect>

namespace view {

class VideoDisplayPolicy {
public:
	virtual QRect getViewportSize(QSize displaySize, QSize videoSize) = 0;
};
} // namespace view
#endif // !_VIDEODISPLAYPOLICY


