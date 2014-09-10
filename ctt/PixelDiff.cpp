#include "PixelDiff.h"

namespace model {
namespace difference {

using ::model::Module;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

PixelDiff::PixelDiff(Module::sptr module1, Module::sptr module2) : FrameDiff(module1, module2) {}

PixelDiff::~PixelDiff() {}

Memento PixelDiff::getMemento() const {
    return FrameDiff::getMemento();
}

void PixelDiff::restore(::model::saveable::Memento memento) {
    FrameDiff::restore(memento);
}

PixelDiff::PixelDiff() : FrameDiff() {
    isDummyFlag = true;
}

}  // namespace difference
}  // namespace model
