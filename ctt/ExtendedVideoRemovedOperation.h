#ifndef _ExtendedVideoRemovedOperation_H
#define _ExtendedVideoRemovedOperation_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "FilteredVideo.h"
#include "Operation.h"
#include "SaveableList.h"
#include "Player.h"

namespace controller {
	namespace operation {

		/**
		* The ExtendedVideoRemovedOperation is providing functionality for doing and undoing removing a Video from two VideoLists.
		*/
		class ExtendedVideoRemovedOperation : public Operation {
		public:
			typedef QScopedPointer<ExtendedVideoRemovedOperation> uptr;
			typedef QSharedPointer<ExtendedVideoRemovedOperation> sptr;
			typedef QWeakPointer<ExtendedVideoRemovedOperation> wptr;

			/**
			* Constructs an Operation that is responsible for removing a specified Video from two VideoLists.
			*
			* @param index The index of a video which should be removed from the list of videos.
			* @param videoList The list from which a certain video should be removed.
			* @param filteredVideos Another list from which a certain video should be removed.
			*/
			ExtendedVideoRemovedOperation(int index, 
											::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList, 
											::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos,
											::model::saveable::SaveableList<::model::player::Player>::sptr playerList);

			/**
			* Manages requests to remove a Video from two VideoLists.
			*/
			void doOperation();

			/**
			* Manages requests to undo removing a Video from a VideoList.
			*/
			void undoOperation();

		private:
			int index;
			::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList;
			::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr filteredVideos;
			::model::saveable::SaveableList<model::player::Player>::sptr playerList;
			::model::saveable::Memento videoListMemento;
			::model::saveable::Memento filteredVideosMemento;
			::model::saveable::Memento playerListMemento;

		};

	}  // namespace operation
}  // namespace controller

#endif  //_ExtendedVideoRemovedOperation_H
