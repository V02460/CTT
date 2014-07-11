#include "Observable.h"
#include <QObject>

namespace model {

void Observable::subscribe(Observer::sptr observer) {
	connect(this, SIGNAL(changed()), observer.data(), SLOT(update()), Qt::UniqueConnection);
}

void Observable::unsubscribe(const Observer &observer) {
	disconnect(this, SIGNAL(changed()), &observer, SLOT(update()));
}

}  // namespace model