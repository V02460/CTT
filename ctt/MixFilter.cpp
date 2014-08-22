#include "MixFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

MixFilter::MixFilter(Module::sptr predecessor, Surface::sptr surface) : Filter(predecessor) {
    throw new NotImplementedException();
}

MixFilter::~MixFilter() {
    throw new NotImplementedException();
}

QString MixFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr MixFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Memento MixFilter::getMemento() const {
    return Filter::getMemento();
}

void MixFilter::restore(Memento memento) {
    Filter::restore(memento);
}

QList<const Module*> MixFilter::getUsesList() const {
    return QList<const Module*>() << this;
}

Saveable::SaveableType MixFilter::getType() const {
	return Saveable::SaveableType::mixFilter;
}

}  // namespace filter
}  // namespace model