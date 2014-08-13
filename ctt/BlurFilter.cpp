#include "BlurFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;
using ::model::saveable::Saveable;

QString BlurFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr BlurFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

Saveable::SaveableType BlurFilter::getType() const {
	return Saveable::SaveableType::blurFilter;
}

}  // namespace filter
}  // namespace model