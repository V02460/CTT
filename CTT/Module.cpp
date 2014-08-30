#include "Module.h"

namespace model {

using ::model::saveable::Saveable;
using ::exception::AccessToDummyException;

bool Module::uses(const Module &module) const {
	if (isDummy()) {
		throw new AccessToDummyException();
	}
    return getUsesList().contains(&module);
}

Saveable::SaveableType Module::getSaveableType() {
    return SaveableType::module;
}

}  // namespace model