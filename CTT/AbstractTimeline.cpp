#include "AbstractTimeline.h"

#include "NotImplementedException.h"

using ::exception::NotImplementedException;

namespace view {

<<<<<<< HEAD
	AbstractTimeline::AbstractTimeline(QWidget *parent) : QWidget(parent) {}
=======
void AbstractTimeline::update() {
	throw NotImplementedException();
}
>>>>>>> master

}  // namespace view