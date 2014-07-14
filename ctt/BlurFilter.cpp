#include "BlurFilter.h"

#include "NotImplementedException.h"

namespace model {
namespace filter {

using ::model::frame::Frame;
using ::exception::NotImplementedException;

QString BlurFilter::getName() const {
    throw new NotImplementedException();
}

model::frame::Frame::sptr BlurFilter::getFrame(unsigned int frameNumber) const {
    throw new NotImplementedException();
}

}  // namespace filter
}  // namespace model