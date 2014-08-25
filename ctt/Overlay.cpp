#include "Overlay.h"

namespace model {
namespace filter {
namespace overlay {

    using ::model::saveable::Saveable;

Overlay::Overlay(Module::sptr predecessor) :Filter(predecessor) {

}

Overlay::~Overlay() {

}

Saveable::SaveableType Overlay::getSaveableType() {
    return SaveableType::overlay;
}

}  // namespace overlay
}  // namespace filter
}  // namespace model