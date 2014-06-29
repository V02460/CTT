


#if !defined(_DIFFERENCECONTROLLER_H)
#define _DIFFERENCECONTROLLER_H

#include "Observer.h"
#include "SaveableList<T extends Saveable>.h"

class DifferenceController : public Observer {
public:
	slot diffInserted(QString id);
	slot diffRemoved(int pos);
private:
	SaveableList<T extends Saveable> *diffList;
};

#endif  //_DIFFERENCECONTROLLER_H
