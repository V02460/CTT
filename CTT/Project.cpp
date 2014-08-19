#include "Project.h"

#include "NotImplementedException.h"

namespace controller {
namespace project {

using ::model::saveable::SaveableList;
using ::model::video::FileVideo;
using ::model::video::Video;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::difference::FrameDiff;
using ::view::ViewState;
using ::exception::NotImplementedException;

Project::Project() : player2(new Player(24.0)) {
	baseVideoList = SaveableList<FileVideo>::sptr(new SaveableList<FileVideo>());
	videoList1 = SaveableList<FilteredVideo>::sptr(new SaveableList<FilteredVideo>());
	videoList2 = SaveableList<Video>::sptr(new SaveableList<Video>());
	playerList1 = SaveableList<Player>::sptr(new SaveableList<Player>());
	diffList = SaveableList<FrameDiff>::sptr(new SaveableList<FrameDiff>());
}

SaveableList<FileVideo>::sptr Project::getBaseVideoList() const {
	return baseVideoList;
}

SaveableList<FilteredVideo>::sptr Project::getVideoList1() const {
	return videoList1;
}

SaveableList<Video>::sptr Project::getVideoList2() const {
	return videoList2;
}

SaveableList<Player>::sptr Project::getPlayerList1() const {
	return playerList1;
}

Player::sptr Project::getPlayer2() const {
	return player2;
}

SaveableList<FrameDiff>::sptr Project::getDiffList() const {
	return diffList;
}

ViewState::sptr Project::getView() const {
    throw new NotImplementedException();
}

}  // namespace project
}  // namespace controller