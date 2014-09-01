#ifndef _INSERTIONWIDGET_H
#define _INSERTIONWIDGET_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QGridLayout>

#include "ListedPushButton.h"

namespace view {

/**
 * Based on the current state of the view the insertion widget enables the user to choose the filter or difference to
 * add to the list views.
 */
class InsertionWidget : public QWidget {
    Q_OBJECT

public:
    typedef QScopedPointer<InsertionWidget> uptr;
    typedef QSharedPointer<InsertionWidget> sptr;
    typedef QWeakPointer<InsertionWidget> wptr;

	InsertionWidget(QWidget *parent = 0);

	// TODO virtual void resizeEvent(QResizeEvent *ev) Q_DECL_OVERRIDE;

protected:
	QSize preferredButtonSize;
	QList<ListedPushButton*> insertionButtons; /**< The list of buttons to insert filters or differences */
	// TODO void rearrangeContents();
	void setupUi();

private:
	// TODO void removeContents();

	QList<QSpacerItem*> spacers;
	QGridLayout *layout;
};

}  // namespace view

#endif  //_INSERTIONWIDGET_H
