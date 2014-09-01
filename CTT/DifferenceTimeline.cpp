#include "DifferenceTimeline.h"

using ::model::saveable::SaveableList;
using ::model::difference::FrameDiff;

namespace view {
	DifferenceTimeline::DifferenceTimeline(SaveableList<FrameDiff>::sptr differences, QWidget *parent) : AbstractTimeline(parent), differences(differences) {

	}

	void DifferenceTimeline::update() {

	}
}  // namespace view