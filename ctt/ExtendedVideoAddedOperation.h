#ifndef _EXTENDEDVIDEOADDEDOPERATION_H
#define _EXTENDEDVIDEOADDEDOPERATION_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Operation.h"
#include "Video.h"
#include "FilteredVideo.h"
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

			/**
			* Constructs an Operation that is responsible for adding a specified Video to a VideoList.
			*
			* @param video The video which should be added to a list of videos.
			* @param videoList The list to which a certain video should be added.
			* @param filteredVideos Another list to which a certain video should be added.
			*/
			ExtendedVideoAddedOperation(::model::filter::FilteredVideo::sptr video1, ::model::filter::FilteredVideo::sptr video2,
				::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList, ::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos);

			/**
			* Manages requests to add a Video to two VideoLists.
			*/
			void doOperation();

			/**
			* Manages requests to undo adding a Video to two VideoLists.
			*/
			void undoOperation();

		private:
			::model::filter::FilteredVideo::sptr video1;
			::model::filter::FilteredVideo::sptr video2;
			int index;
			::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList;
			::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
			::model::saveable::Memento memento;

		};

	}  // namespace operation
}  // namespace controller

#endif  //_VIDEOADDEDOPERATION_H
