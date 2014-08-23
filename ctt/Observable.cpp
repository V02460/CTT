#include "Observable.h"

namespace model {

void Observable::subscribe(Observer::sptr observer) {
	if (!observers.contains(observer)) {
		observers.append(observer);
	}
}

void Observable::unsubscribe(const Observer &observer) {
	for each (Observer::sptr subscribedObserver in observers)
	{
		if (subscribedObserver.data() == &observer)
		{
			observers.removeOne(subscribedObserver);
			return;
		}
	}
}

void Observable::changed()
{
	for each (Observer::sptr observer in observers)
	{
		observer->update();
	}
}


}  // namespace model