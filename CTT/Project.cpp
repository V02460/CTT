#include "Project.h"

namespace controller {
namespace project {

using ::model::SaveableList;
using ::model::video::FileVideo;
using ::model::video::Video;
using ::model::filter::FilteredVideo;
using ::model::player::Player;
using ::model::difference::FrameDiff;
using ::view::ViewState;

Project::Project() {
}

SaveableList<const FileVideo&> Project::getBaseVideoList() const {
}

SaveableList<const FilteredVideo&> Project::getVideoList1() const {
}

SaveableList<const Video&> Project::getVideoList2() const {
}

SaveableList<const Player&> Project::getPlayerList1() const {
}

const Player &Project::getPlayer2() const {
}

SaveableList<const FrameDiff&> Project::getDiffList() const {
}

ViewState Project::getView() const {
}

}  // namespace project
}  // namespace controller