#include "CoffeeFilter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {

using ::model::frame::Frame;

CoffeeFilter::CoffeeFilter(Module::sptr predecessor) : Filter(predecessor) {

}

CoffeeFilter::~CoffeeFilter() {

}

QString CoffeeFilter::getName() const {

}

model::frame::Frame::sptr CoffeeFilter::getFrame(unsigned int frameNumber) const {

}

}  // namespace filter
}  // namespace model