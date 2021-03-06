#ifndef _VIDEOLISTOPERATION_H
#define _VIDEOLISTOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "Video.h"
#include "SaveableList.h"

namespace controller {
namespace operation {

/**
 * The VideoListOperation is providing functionality for doing and undoing manipulations of the VideoList which is used
 * for generating test videos or analyzing.
 */
class VideoListOperation : public Operation {
public:
    typedef QScopedPointer<VideoListOperation> uptr;
    typedef QSharedPointer<VideoListOperation> sptr;
    typedef QWeakPointer<VideoListOperation> wptr;

    /**
     * Manages requests to manipulate the VideoList which is used for generating test videos or analysing.
     */
    virtual void doOperation() = 0;

    /**
     * Manages requests to undo manipulations of the VideoList which is used for generating test videos or analysing.
     */
    virtual void undoOperation() = 0;
protected:
    ::model::video::Video::sptr video;
    int index;
    ::model::saveable::SaveableList<::model::video::Video> videoList;
};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOLISTOPERATION_H
