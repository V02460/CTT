#include "VideoAnalysingWidget.h"

#include "NotImplementedException.h"

namespace view {

using ::exception::NotImplementedException;

QString VideoAnalysingWidget::getOverlay() const {
    throw new NotImplementedException();
}

void VideoAnalysingWidget::comboboxOverlayCurrentIndexChanged(int index) {
    throw new NotImplementedException();
}

}  // namespace view