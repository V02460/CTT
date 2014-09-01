#include "ExtendedVideoAddedOperation.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "VideoScrubber.h"

namespace controller {
namespace operation {

using ::model::video::Video;
using ::model::saveable::SaveableList;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::player::VideoScrubber;

ExtendedVideoAddedOperation::ExtendedVideoAddedOperation(SaveableList<Player>::sptr playerList,
			                                             FilteredVideo::sptr video1,
														 FilteredVideo::sptr video2,
														 SaveableList<FilteredVideo>::sptr videoList,
														 SaveableList<FilteredVideo>::sptr filteredVideos)
		: video1(video1),
		  video2(video2),
		  videoList(videoList),
		  filteredVideos(filteredVideos),
		  index(videoList->getSize()),
		  playerList(playerList) {}

void ExtendedVideoAddedOperation::doOperation() {
	double fps = video1->getMetadata().getFPS();

	videoList->insert(index, video1);
	filteredVideos->insert(index, video2);	

	VideoScrubber::sptr scrub1(new VideoScrubber(video1));
	VideoScrubber::sptr scrub2(new VideoScrubber(video2));
	Player *player = new Player(fps);
	player->addScrubber(scrub1, 0);
	player->addScrubber(scrub2, 1);

	playerList->insert(index, QSharedPointer<Player>(player));

}

void ExtendedVideoAddedOperation::undoOperation() {
	videoList->remove(index);
	filteredVideos->remove(index);
	playerList->remove(index);
}

}  // namespace operation
}  // namespace controller