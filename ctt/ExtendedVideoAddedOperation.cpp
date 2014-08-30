#include "ExtendedVideoAddedOperation.h"
#include "FilteredVideo.h"

namespace controller {
	namespace operation {

		using ::model::video::Video;
		using ::model::saveable::SaveableList;
		using ::model::filter::FilteredVideo;

		ExtendedVideoAddedOperation::ExtendedVideoAddedOperation(FilteredVideo::sptr video1, FilteredVideo::sptr video2, SaveableList<FilteredVideo>::sptr videoList, SaveableList<FilteredVideo>::sptr filteredVideos) : video1(video1), video2(video2), videoList(videoList), filteredVideos(filteredVideos){

		}

		void ExtendedVideoAddedOperation::doOperation() {
			index = videoList->getSize();

			videoList->insert(index, video1);
			filteredVideos->insert(index, video2);			
		}

		void ExtendedVideoAddedOperation::undoOperation() {
			videoList->remove(index);
			filteredVideos->remove(index);
		}

	}  // namespace operation
}  // namespace controller