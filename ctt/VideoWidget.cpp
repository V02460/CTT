#include "VideoWidget.h"

#include "NotImplementedException.h"

namespace view {

using ::model::player::VideoScrubber;
using ::exception::NotImplementedException;

VideoWidget::VideoWidget(VideoScrubber::sptr scrubber) {
    throw new NotImplementedException();
}

const VideoScrubber &VideoWidget::getScrubber() const {
    throw new NotImplementedException();
}

}  // namespace view