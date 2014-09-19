#include "Observable.h"

namespace model {

void Observable::subscribe(Observer *observer) {
	if (!observers.contains(observer)) {
		observers.append(observer);
	}
}

void Observable::unsubscribe(const Observer *observer) {
	for each (Observer *subscribedObserver in observers) {
		if (subscribedObserver == observer) {
			observers.removeOne(subscribedObserver);
			return;
		}
	}
}

void Observable::changed() {
	for (int i = 0; i < observers.size(); i++) {
		observers[i]->update();
	}
}


}  // namespace model