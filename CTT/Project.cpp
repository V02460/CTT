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

Project::Project() {
	baseVideoList = *new QSharedPointer<SaveableList<FileVideo>>(new SaveableList<FileVideo>());
	videoList1 = *new QSharedPointer<SaveableList<FilteredVideo>>(new SaveableList<FilteredVideo>());
	videoList2 = *new QSharedPointer<SaveableList<FilteredVideo>>(new SaveableList<FilteredVideo>());
	playerList1 = *new QSharedPointer<SaveableList<Player>>(new SaveableList<Player>());
	player2 = *new QSharedPointer<Player>(new Player(24.0));
	diffList = *new QSharedPointer<SaveableList<FrameDiff>>(new SaveableList<FrameDiff>());
	view = ViewState::getInstance();
}

SaveableList<FileVideo>::sptr Project::getBaseVideoList() const {
	return baseVideoList;
}

SaveableList<FilteredVideo>::sptr Project::getVideoList1() const {
	return videoList1;
}

SaveableList<FilteredVideo>::sptr Project::getVideoList2() const {
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
	return view;
}

}  // namespace project
}  // namespace controller