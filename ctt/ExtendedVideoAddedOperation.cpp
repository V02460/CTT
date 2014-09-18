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
        : playerList(playerList)
        , video1(video1)
        , video2(video2)
        , videoList(videoList)
        , filteredVideos(filteredVideos)
        , index(videoList->getSize()) {
}

void ExtendedVideoAddedOperation::doOperation() {
    double fps = video1->getMetadata().getFPS();

	VideoScrubber::sptr scrubber1(new VideoScrubber(video1));
	VideoScrubber::sptr scrubber2(new VideoScrubber(video2));

	Player::sptr player(new Player(fps));
	player->addScrubber(scrubber1, 0);
	player->addScrubber(scrubber2, 1);

	playerList->insert(index, player);
    videoList->insert(index, video1);
    filteredVideos->insert(index, video2);
}

void ExtendedVideoAddedOperation::undoOperation() {
    videoList->remove(index);
    filteredVideos->remove(index);
    playerList->remove(index);
}

}  // namespace operation
}  // namespace controller