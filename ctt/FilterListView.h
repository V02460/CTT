#if !defined(_FILTERLISTVIEW_H)
#define _FILTERLISTVIEW_H

#include "AbstractListView.h"
#include "Filter.h"
#include "FilterParam.h"

namespace view {
namespace base_components {

class FilterListView : public AbstractListView {
public:
	signal filterMoved(int oldPos, int newPos);
	void filterParamChanged(Filter filter, FilterParam param);
};

}  // namespace base_components
}  // namespace view

#endif  //_FILTERLISTVIEW_H
