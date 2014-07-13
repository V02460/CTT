#include "Project.h"

namespace controller {
namespace project {

using ::model::saveable::SaveableList;
using ::model::video::FileVideo;
using ::model::video::Video;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::difference::FrameDiff;
using ::view::ViewState;

Project::Project() : player2(24.0) {
}

SaveableList<FileVideo>::sptr Project::getBaseVideoList() const {
}

SaveableList<FilteredVideo>::sptr Project::getVideoList1() const {
}

SaveableList<Video>::sptr Project::getVideoList2() const {
}

SaveableList<Player>::sptr Project::getPlayerList1() const {
}

Player::sptr Project::getPlayer2() const {
}

SaveableList<FrameDiff>::sptr Project::getDiffList() const {
}

ViewState::sptr Project::getView() const {
}

}  // namespace project
}  // namespace controller