#include "ExtendedVideoRemovedOperation.h"

#include "FilteredVideo.h"

namespace controller {
	namespace operation {

		using ::model::saveable::SaveableList;
		using ::model::filter::FilteredVideo;

		ExtendedVideoRemovedOperation::ExtendedVideoRemovedOperation(int index, SaveableList<FilteredVideo>::sptr videoList, SaveableList<FilteredVideo>::sptr filteredVideos) : index(index), video1(videoList->get(index)), video2(filteredVideos->get(index)), videoList(videoList), filteredVideos(filteredVideos){

		}

		void ExtendedVideoRemovedOperation::doOperation() {
			videoList->remove(index);
			filteredVideos->remove(index);
		}

		void ExtendedVideoRemovedOperation::undoOperation() {
			videoList->insert(index, video1);
			filteredVideos->insert(index, video2);
		}

	}  // namespace operation
}  // namespace controller