#include "Observable.h"

namespace model {

const QString Observable::observersStringId = "observer";

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

void Observable::saveObserversToMemento(model::saveable::Memento memento)
{
	memento.setUInt(numberOfObserversStringId, observers.size());
	for (unsigned int i = 0; i < static_cast<unsigned int>(observers.size()); i++)
	{
		memento.setSharedPointer(observersStringId + QString::number(i), observers[i]);
	}
}

void Observable::restoreObserversFromMemento(model::saveable::Memento memento)
{
	observers.clear();
	for (unsigned int i = 0; i < memento.getUInt(numberOfObserversStringId); i++)
	{
		observers.append(memento.getSharedPointer(observersStringId + QString::number(i)).dynamicCast<Observer>());
	}
}

}  // namespace model