#include "FrameDiff.h"

namespace model {
namespace difference {

using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::exception::AccessToDummyException;

FrameDiff::FrameDiff(Module::sptr module1, Module::sptr module2) : module1(module1), module2(module2) {}

FrameDiff::~FrameDiff() {}

unsigned int FrameDiff::getFrameCount() const {
	if (isDummy()) {
		throw AccessToDummyException();
	}

    return qMin(module1->getFrameCount(), module2->getFrameCount());
}

Module::sptr FrameDiff::getModule1() {
    return module1;
}

Module::sptr FrameDiff::getModule2() {
    return module2;
}

Memento FrameDiff::getMemento() const {
    Memento memento;

    memento.setSharedPointer("module1", module1);
    memento.setSharedPointer("module2", module2);

    return memento;
}

void FrameDiff::restore(Memento memento) {
    module1 = memento.getSharedPointer("module1").dynamicCast<Module>();
    module2 = memento.getSharedPointer("module2").dynamicCast<Module>();
}

FrameDiff::FrameDiff() {
    isDummyFlag = true;
}

Saveable::SaveableType FrameDiff::getSaveableType() {
    return SaveableType::frameDiff;
}

}  // namespace difference
}  // namespace model