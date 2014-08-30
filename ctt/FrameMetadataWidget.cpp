#include "FrameMetadataWidget.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

using ::model::player::VideoScrubber;

FrameMetadataWidget::FrameMetadataWidget(VideoScrubber::sptr scrubber) {

}

void FrameMetadataWidget::update() {
	throw new NotImplementedException();
}

}  // namespace view