#if !defined(_VIEWTYPE_H)
#define _VIEWTYPE_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace view {

/**
 *	Identifies the current view state.
 */
enum ViewType {
	/*The identifier for the analysing view.*/
	ANALYSING_VIEW,
	/*The identifier fir the processing view.*/
	PROCESSING_VIEW
};

}  // namespace view

#endif  //_VIEWTYPE_H
