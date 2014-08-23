#ifndef _VIDEODISPLAYPOLICY
#define _VIDEODISPLAYPOLICY

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QRect>

namespace view {

class VideoDisplayPolicy {
public:
	typedef QScopedPointer<VideoDisplayPolicy> uptr;
	typedef QSharedPointer<VideoDisplayPolicy> sptr;
	typedef QWeakPointer<VideoDisplayPolicy> wptr;

	virtual QRect getViewportSize(QSize displaySize, QSize videoSize) const = 0;

private:
	VideoDisplayPolicy();
};
} // namespace view
#endif // !_VIDEODISPLAYPOLICY


