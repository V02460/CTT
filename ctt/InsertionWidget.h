


#if !defined(_INSERTIONWIDGET_H)
#define _INSERTIONWIDGET_H

#include "ViewState.h"

class InsertionWidget {
public:
	List<QPushButtons> insertionButton;
	ViewState viewState;
	slot changeViewState();
};

#endif  //_INSERTIONWIDGET_H
