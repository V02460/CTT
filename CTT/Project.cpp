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

Project::Project() : player2(24.0) {
    throw new NotImplementedException();
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

}  // namespace project
}  // namespace controller