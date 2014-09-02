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

QList<const Module*> Module::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::SaveableType Module::getSaveableType() {
	return Saveable::module;
}

}  // namespace model