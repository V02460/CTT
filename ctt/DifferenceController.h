


#if !defined(_DIFFERENCECONTROLLER_H)
#define _DIFFERENCECONTROLLER_H

#include "Observer.h"
#include "SavableList<T extends Savable>.h"

class DifferenceController : public Observer {
public:
	slot diffInserted(QString id);
	slot diffRemoved(int pos);
private:
	SavableList<T extends Savable> *diffList;
};

#endif  //_DIFFERENCECONTROLLER_H
