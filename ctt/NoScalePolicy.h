#ifndef _NOSCALEPOLICY
#define _NOSCALEPOLICY

#include "VideoDisplayPolicy.h"

namespace view {

class NoScalePolicy : public VideoDisplayPolicy {
public:
	NoScalePolicy();
	virtual QRect getViewportSize(QSize displaySize, QSize videoSize) Q_DECL_OVERRIDE;
};

} // namespace view

#endif // !_NOSCALEPOLICY
