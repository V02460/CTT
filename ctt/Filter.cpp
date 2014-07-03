#include "Filter.h"
#include "Module.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::Module;

Filter::Filter(Module::sptr predecessor) {

}

Filter::~Filter() {

}

QList<FilterParam> Filter::getParams() const {

}

void Filter::setParam(FilterParam parameter) {

}

void Filter::setPreviousModule(Module::sptr previous) {

}

void Filter::activate(UIntegerInterval interval) {

}

void Filter::deactivate(UIntegerInterval interval) {

}

}  // namespace filter
}  // namespace model