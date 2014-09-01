#include "AbstractTimeline.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

	AbstractTimeline::AbstractTimeline(QWidget *parent) : QWidget(parent) {}

}  // namespace view