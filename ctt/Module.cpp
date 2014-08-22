#include "Module.h"

namespace model {

bool Module::uses(const Module &module) const {
    return getUsesList().contains(&module);
}

}  // namespace model