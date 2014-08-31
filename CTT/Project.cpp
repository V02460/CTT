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
using ::exception::NotImplementedException;
using ::view::ViewState;
using ::view::ViewType;

Project::Project() : Observable(),
					 baseVideoList(new SaveableList<FilteredVideo>()),
	                 videoList1(new SaveableList<FilteredVideo>()),
	                 videoList2(new SaveableList<FilteredVideo>()),
	                 playerList1(new SaveableList<Player>()),
	                 player2(new Player(24)),
	                 diffList(new SaveableList<FrameDiff>()) {}

SaveableList<FilteredVideo>::sptr Project::getBaseVideoList() const {
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

void Project::clear() {
	baseVideoList->restore(SaveableList<FilteredVideo>().getMemento());
	videoList1->restore(SaveableList<FilteredVideo>().getMemento());
	videoList2->restore(SaveableList<FilteredVideo>().getMemento());
	playerList1->restore(SaveableList<Player>().getMemento());
	player2->restore(Player(24).getMemento());
	diffList->restore(SaveableList<FrameDiff>().getMemento());
	ViewState::getInstance()->changeView(ViewType::PROCESSING_VIEW);
	everythingChanged();
}

void Project::everythingChanged() {
	changed();
}

Project *Project::getInstance() {
	if (instance.isNull()) {
		instance.reset(new Project());
	}
	return instance.data();
}

Project::uptr Project::instance;

}  // namespace project
}  // namespace controller