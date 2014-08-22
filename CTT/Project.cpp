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

Project::Project() : baseVideoList(new SaveableList<FileVideo>()),
	                 videoList1(new SaveableList<FilteredVideo>()),
	                 videoList2(new SaveableList<FilteredVideo>()),
	                 playerList1(new SaveableList<Player>()),
	                 player2(new Player(24)),
	                 diffList(new SaveableList<FrameDiff>()),
	                 view(new ViewState()), // TODO later singelton -> getInstance()
	                 context(new QOpenGLContext()),
                     offscreenSurface() {
    offscreenSurface.create();
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

Project *Project::getInstance() {
	if (instance.isNull()) {
		instance.reset(new Project());
	}
	return instance.data();
}

QOpenGLContext *Project::getActiveContext() const {
    context->makeCurrent(&offscreenSurface);
    return context.data();
}

Project::uptr Project::instance;

}  // namespace project
}  // namespace controller