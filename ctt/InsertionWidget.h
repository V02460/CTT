#ifndef _INSERTIONWIDGET_H
#define _INSERTIONWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QGridLayout>

#include "ViewState.h"
#include "Observer.h"
#include "FilterController.h"
#include "OverlayController.h"
#include "ListedPushButton.h"

namespace view {

/**
 * Based on the current state of the view the insertion widget enables the user to choose the filter or difference to
 * add to the list views.
 */
class InsertionWidget : public QWidget, public::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<InsertionWidget> uptr;
    typedef QSharedPointer<InsertionWidget> sptr;
    typedef QWeakPointer<InsertionWidget> wptr;

	InsertionWidget(QWidget *parent = 0);

	//virtual void resizeEvent(QResizeEvent *ev) Q_DECL_OVERRIDE;

signals:
	void inserted(QString id);

protected:
	QSize preferredButtonSize;
	QList<ListedPushButton::sptr> insertionButtons; /**< The list of buttons to insert filters or differences */
	//void rearrangeContents();
	void setupUi();
private:
	//void removeContents();

	QList<QSpacerItem*> spacers;
	QGridLayout *layout;
};

}  // namespace view

#endif  //_INSERTIONWIDGET_H
