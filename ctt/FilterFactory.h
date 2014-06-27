


#if !defined(_FILTERFACTORY_H)
#define _FILTERFACTORY_H

#include "Filter.h"

class FilterFactory {
public:
	List<QString> getAllFilterIDs();
	Filter createFilter(QString id);
private:
	void FilterFactory();
};

#endif  //_FILTERFACTORY_H
