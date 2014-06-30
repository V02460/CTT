#if !defined(_VIDEOREMOVEDOPERATION_H)
#define _VIDEOREMOVEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "VideoListOperation.h"

namespace controller {
namespace operation {

/**
*	The VideoRemovedOperation is providing functionality for doing and undoing removing a Video from a VideoList.
**/
class VideoRemovedOperation : public VideoListOperation {
public:
	typedef QScopedPointer<VideoRemovedOperation> uptr;
	typedef QSharedPointer<VideoRemovedOperation> sptr;
	typedef QWeakPointer<VideoRemovedOperation> wptr;


	/**
	*	Constructs an Operation that is responsible for removing a specified Video from a VideoList.
	*	@param video The video which should be added to a list of videos.
	*	@param videoList The list to which a certain video should be added.
	**/
	VideoRemovedOperation(int index, int SaveableList<Video>);

	/**
	*	Manages requests to remove a Video from a VideoList.
	**/
	void doOperation();

	/**
	*	Manages requests to undo removing a Video from a VideoList.
	**/
	void undoOperation();
};

}  // namespace operation
}  // namespace controller

#endif  //_VIDEOREMOVEDOPERATION_H
