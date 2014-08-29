#ifndef _DIFFERENCEINSERTIONWIDGET
#define _DIFFERENCEINSERTIONWIDGET

#include "InsertionWidget.h"
#include "DifferenceController.h"
#include "AnalysingOrderingWidget.h"

namespace view {
class DifferenceInsertionWidget : public InsertionWidget
{
public:
	typedef QScopedPointer<DifferenceInsertionWidget> uptr;
	typedef QSharedPointer<DifferenceInsertionWidget> sptr;
	typedef QWeakPointer<DifferenceInsertionWidget> wptr;

	DifferenceInsertionWidget(::controller::DifferenceController::sptr differenceController,
		AnalysingOrderingWidget::sptr orderingWidget, QWidget *parent = 0);

	virtual void update() Q_DECL_OVERRIDE;
};
}
#endif

