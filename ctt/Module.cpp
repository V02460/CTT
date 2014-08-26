#include "Module.h"

namespace model {

using ::model::saveable::Saveable;

bool Module::uses(const Module &module) const {
    return getUsesList().contains(&module);
}

Saveable::SaveableType Module::getSaveableType() {
    return SaveableType::module;
}

}  // namespace model