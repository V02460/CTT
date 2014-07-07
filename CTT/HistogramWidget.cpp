#include "HistogramWidget.h"

namespace view {

HistogramWidget::HistogramWidget(::model::player::VideoScrubber::sptr scrubber);

void HistogramWidget::next();

void HistogramWidget::paint();

}  // namespace view