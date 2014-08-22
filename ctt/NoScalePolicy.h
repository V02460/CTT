#ifndef _NOSCALEPOLICY
#define _NOSCALEPOLICY

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "VideoDisplayPolicy.h"

namespace view {

class NoScalePolicy : public VideoDisplayPolicy {
public:
	typedef QScopedPointer<NoScalePolicy> uptr;
	typedef QSharedPointer<NoScalePolicy> sptr;
	typedef QWeakPointer<NoScalePolicy> wptr;

	NoScalePolicy();
	virtual QRect getViewportSize(QSize displaySize, QSize videoSize) Q_DECL_OVERRIDE;
};

} // namespace view

#endif // !_NOSCALEPOLICY
