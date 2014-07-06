#include "Project.h"

namespace controller {

class Project {

    Project();

    ::model::SaveableList<const ::model::video::FileVideo&> getBaseVideoList() const;

    ::model::SaveableList<const ::model::filter::FilteredVideo&> getVideoList1() const;

    ::model::SaveableList<const ::model::video::Video&> getVideoList2() const;

    ::model::SaveableList<const ::model::player::Player&> getPlayerList1() const;

    const ::model::player::Player &getPlayer2() const;

    ::model::SaveableList<const ::model::difference::FrameDiff&> getDiffList() const;

    ::view::ViewState getView() const;

private:
    ::model::SaveableList<::model::video::FileVideo> baseVideoList;
    ::model::SaveableList<::model::filter::FilteredVideo> videoList1;
    ::model::SaveableList<::model::filter::FilteredVideo> videoList2;
    ::model::SaveableList<::model::player::Player> playerList1;
    ::model::player::Player player2;
    ::model::SaveableList<model::difference::FrameDiff> diffList;
    view::ViewState view;
};

}  // namespace controller