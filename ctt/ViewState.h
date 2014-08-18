#ifndef _VIEWSTATE_H
#define _VIEWSTATE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>

#include "ViewType.h"
#include "VideoDisplayPolicy.h"
#include "Observable.h"
#include "Saveable.h"
#include "Memento.h"

namespace view {

/**
 * The view state class determines the state the GUI is currently in and notifies all relevant components when the
 * state changes.
 */
class ViewState : public QObject, public model::Observable, public ::model::saveable::Saveable {
    Q_OBJECT
public:
    typedef QScopedPointer<ViewState> uptr;
    typedef QSharedPointer<ViewState> sptr;
    typedef QWeakPointer<ViewState> wptr;

    virtual ::model::saveable::Memento getMemento() const;
    virtual void restore(::model::saveable::Memento memento);
	static ::model::saveable::Saveable::sptr getDummy();
	virtual ::model::saveable::Saveable::SaveableType getType() const;

	static QSharedPointer<ViewState> getInstance();
	QSharedPointer<VideoDisplayPolicy> getCurrentVideoDisplayPolicy();

public slots:
    /**
     * Changes the internal viewType and notifies all Observers about the state change.
     */
    void changeView(ViewType newView);

	void changeVideoDisplayPolicy();

signals:
	void videoDisplayPolicyChanged();
	void viewTypeChanged();

private:
	ViewState();

	QSharedPointer<ViewState> instance;
    ViewType currentView;
	QSharedPointer<VideoDisplayPolicy> currentVideoDisplayPolicy;
};

}  // namespace view

#endif  //_VIEWSTATE_H
