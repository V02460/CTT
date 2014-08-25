#include "NoiseFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

NoiseFilter::NoiseFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

NoiseFilter::~NoiseFilter() {
    throw new NotImplementedException();
}

QString NoiseFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr NoiseFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Memento NoiseFilter::getMemento() const {
    return Filter::getMemento();
}

void NoiseFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> NoiseFilter::getUsesList() const {
    throw new NotImplementedException();
}

bool NoiseFilter::uses(const Module &module) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model