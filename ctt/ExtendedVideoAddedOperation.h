#ifndef _EXTENDEDVIDEOADDEDOPERATION_H
#define _EXTENDEDVIDEOADDEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "Video.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "SaveableList.h"

namespace controller {
namespace operation {

/**
* The VideoAddedOperation is providing functionality for doing and undoing adding a Video to two VideoLists.
*/
class ExtendedVideoAddedOperation : public Operation {
public:
	typedef QScopedPointer<ExtendedVideoAddedOperation> uptr;
	typedef QSharedPointer<ExtendedVideoAddedOperation> sptr;
	typedef QWeakPointer<ExtendedVideoAddedOperation> wptr;

    // TODO:
	/**
     * Constructs an Operation that is responsible for adding a specified Video to two two video lists.
     *
     * @param playerList 
     * @param video1 
     * @param video2
     * @param videoList 
     * @param filteredVideos
     */
	ExtendedVideoAddedOperation(::model::saveable::SaveableList<::model::player::Player>::sptr playerList,
                                ::model::filter::FilteredVideo::sptr video1,
                                ::model::filter::FilteredVideo::sptr video2,
		                        ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList,
                                ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos);

    /**
     * Manages requests to add a Video to two VideoLists.
     */
	void doOperation();

    /**
     * Manages requests to undo adding a Video to two VideoLists.
     */
	void undoOperation();

private:
	::model::saveable::SaveableList<model::player::Player>::sptr playerList;
	::model::filter::FilteredVideo::sptr video1;
	::model::filter::FilteredVideo::sptr video2;
	int index;
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList;
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
	::model::saveable::Memento memento;

	::model::saveable::Memento videoListMemento;
	::model::saveable::Memento filteredVideosMemento;
	::model::saveable::Memento playerListMemento;
};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOADDEDOPERATION_H
