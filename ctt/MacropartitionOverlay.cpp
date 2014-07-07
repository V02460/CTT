#include "MacropartitionOverlay.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;

MacropartionOverlay::MacropartionOverlay(Module::sptr predecessor) : Overlay(predecessor) {

}

MacropartionOverlay::~MacropartionOverlay() {

}

QString MacropartionOverlay::getName() const {

}

Frame MacropartionOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namcespace model