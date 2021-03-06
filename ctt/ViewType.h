#ifndef _VIEWTYPE_H
#define _VIEWTYPE_H

namespace view {

/**
 * Identifies the current view state.
 */
enum ViewType {
    /*The identifier for the analysing view.*/
    ANALYSING_VIEW,
    /*The identifier for the processing view.*/
    PROCESSING_VIEW,
	ABX_VIEW
};

}  // namespace view

#endif  //_VIEWTYPE_H
