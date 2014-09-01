#include "Module.h"

namespace model {

using ::model::saveable::Saveable;
using ::exception::AccessToDummyException;

bool Module::uses(const Module &module) const {
	if (isDummy()) {
		throw AccessToDummyException();
	}
    return getUsesList().contains(&module);
}

Saveable::SaveableType Module::getSaveableType() {
	return Saveable::module;
}

}  // namespace model