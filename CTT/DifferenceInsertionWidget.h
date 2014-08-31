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

signals:
	void inserted(QString id, ::model::video::Video::sptr video1, ::model::video::Video::sptr video2);

private slots:
	void listedPushButtonClicked(bool checked, int id);

private:
	void generateButtons();

	::controller::DifferenceController::sptr differenceController;
	AnalysingOrderingWidget::sptr orderingWidget;
};
}
#endif

