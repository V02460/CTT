#ifndef _FILTERINSERTIONWIDGET_H
#define _FILTERINSERTIONWIDGET_H

#include "InsertionWidget.h"

namespace view {

class FilterInsertionWidget : public InsertionWidget {
	Q_OBJECT

public:
	typedef QScopedPointer<FilterInsertionWidget> uptr;
	typedef QSharedPointer<FilterInsertionWidget> sptr;
	typedef QWeakPointer<FilterInsertionWidget> wptr;

	FilterInsertionWidget(controller::FilterController::sptr, QWidget *parent);

private slots:
	void listedButtonClicked(bool checked, int id);

private:
	void generateButtons();

	::controller::FilterController::sptr filterController;
};

} // namespace view

#endif //_FILTERINSERTIONWIDGET_H