#include "CoffeeFilter.h"
#include "Frame.h"
#include "Memento.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

CoffeeFilter::CoffeeFilter(Module::sptr predecessor) : Filter(predecessor) {
    throw new NotImplementedException();
}

CoffeeFilter::~CoffeeFilter() {
    throw new NotImplementedException();
}

QString CoffeeFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr CoffeeFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType CoffeeFilter::getType() const {
	return Saveable::SaveableType::coffeeFilter;
}

}  // namespace filter
}  // namespace model