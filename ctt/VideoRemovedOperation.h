#ifndef _VIDEOREMOVEDOPERATION_H
#define _VIDEOREMOVEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "FilteredVideo.h"
#include "Operation.h"
#include "SaveableList.h"

namespace controller {
namespace operation {

/**
 * The VideoRemovedOperation is providing functionality for doing and undoing removing a Video from a VideoList.
 */
class VideoRemovedOperation : public Operation {
public:
    typedef QScopedPointer<VideoRemovedOperation> uptr;
    typedef QSharedPointer<VideoRemovedOperation> sptr;
    typedef QWeakPointer<VideoRemovedOperation> wptr;

    /**
     * Constructs an Operation that is responsible for removing a specified Video from a VideoList.
     *
     * @param index The index of a video which should be removed from the list of videos.
     * @param videoList The list from which a certain video should be removed.
     */
    VideoRemovedOperation(int index, ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList);

    /**
     * Manages requests to remove a Video from a VideoList.
     */
    void doOperation();

    /**
     * Manages requests to undo removing a Video from a VideoList.
     */
    void undoOperation();

private:
	::model::filter::FilteredVideo::sptr video;
	int index;
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList;
};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOREMOVEDOPERATION_H
