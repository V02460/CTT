#include "HistogramWidget.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

HistogramWidget::HistogramWidget(::model::player::VideoScrubber::sptr scrubber) {

}

void HistogramWidget::next() {

}

void HistogramWidget::paint() {

}

void HistogramWidget::update() {
	throw new NotImplementedException();
}

}  // namespace view