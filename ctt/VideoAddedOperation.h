#ifndef _VIDEOADDEDOPERATION_H
#define _VIDEOADDEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "VideoListOperation.h"
#include "Video.h"
#include "SaveableList.h"

namespace controller {
namespace operation {

/**
 * The VideoAddedOperation is providing functionality for doing and undoing adding a Video to a VideoList.
 */
class VideoAddedOperation : public VideoListOperation {
public:
    typedef QScopedPointer<VideoAddedOperation> uptr;
    typedef QSharedPointer<VideoAddedOperation> sptr;
    typedef QWeakPointer<VideoAddedOperation> wptr;

    /**
     * Constructs an Operation that is responsible for adding a specified Video to a VideoList.
     *
     * @param video The video which should be added to a list of videos.
     * @param videoList The list to which a certain video should be added.
     */
    VideoAddedOperation(::model::video::Video::sptr video,
                        ::model::saveable::SaveableList<::model::video::Video>::sptr videoList);

    /**
     * Manages requests to add a Video to a VideoList.
     */
    void doOperation();

    /**
     * Manages requests to undo adding a Video to a VideoList.
     */
    void undoOperation();

private:
	::model::video::Video::sptr video;

};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOADDEDOPERATION_H
