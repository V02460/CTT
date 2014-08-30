#include "Module.h"

namespace model {

using ::model::saveable::Saveable;

bool Module::uses(const Module &module) const {
    return getUsesList().contains(&module);
}

Saveable::SaveableType Module::getSaveableType() {
	return Saveable::module;
}

}  // namespace model