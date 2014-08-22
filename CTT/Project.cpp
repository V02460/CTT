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
    throw new NotImplementedException();
}

SaveableList<FilteredVideo>::sptr Project::getVideoList1() const {
    throw new NotImplementedException();
}

SaveableList<FilteredVideo>::sptr Project::getVideoList2() const {
    throw new NotImplementedException();
}

SaveableList<Player>::sptr Project::getPlayerList1() const {
    throw new NotImplementedException();
}

Player::sptr Project::getPlayer2() const {
    throw new NotImplementedException();
}

SaveableList<FrameDiff>::sptr Project::getDiffList() const {
    throw new NotImplementedException();
}

ViewState::sptr Project::getView() const {
    throw new NotImplementedException();
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