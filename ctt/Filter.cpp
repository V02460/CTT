#include "Filter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::model::Module;
using ::model::saveable::Memento;
using ::exception::NotImplementedException;

Filter::Filter(Module::sptr predecessor) {
    throw new NotImplementedException();
}

Filter::~Filter() {
    throw new NotImplementedException();
}

QList<FilterParam> Filter::getParams() const {
    throw new NotImplementedException();
}

void Filter::setParam(FilterParam parameter) {
    throw new NotImplementedException();
}

void Filter::setPreviousModule(Module::sptr previous) {
    throw new NotImplementedException();
}

void Filter::activate(UIntegerInterval interval) {
    throw new NotImplementedException();
}

void Filter::deactivate(UIntegerInterval interval) {
    throw new NotImplementedException();
}

unsigned int Filter::getFrameCount() const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model