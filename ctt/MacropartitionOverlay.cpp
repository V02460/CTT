#include "MacropartitionOverlay.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {
namespace overlay {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

MacropartionOverlay::MacropartionOverlay(Module::sptr predecessor) : Overlay(predecessor) {
    throw new NotImplementedException();
}

MacropartionOverlay::~MacropartionOverlay() {
    throw new NotImplementedException();
}

QString MacropartionOverlay::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MacropartionOverlay::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace overlay
}  // namespace filter
}  // namespace model