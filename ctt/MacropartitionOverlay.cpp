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

model::frame::Frame::sptr MacropartionOverlay::getFrame(unsigned int frameNumber) const {

}

}  // namespace overlay
}  // namespace filter
}  // namcespace model