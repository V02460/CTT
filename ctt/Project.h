#ifndef _PROJECT_H
#define _PROJECT_H

#include "SaveableList.h"
#include "Video.h"
#include "FileVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "FrameDiff.h"
#include "ViewState.h"

namespace controller {
namespace project {

/**
 * The project contains all savable objects that already exist in an empty project.
 */
class Project {

public:
    typedef QScopedPointer<Project> uptr;
    typedef QSharedPointer<Project> sptr;
    typedef QWeakPointer<Project> wptr;

    /**
	* Creates a new project and all savable objects needed from the start of the program.
     */
    Project();

    /**
     * Returns the list of all base videos the project uses, i.e. videos which are directly read from files.
     *
     * @return SaveableList<FileVideo> the list of all base videos the project uses.
     */
	::model::saveable::SaveableList<::model::video::FileVideo>::sptr getBaseVideoList() const;

    /**
     * Returns the List of all FilteredVideos the Project uses in the first view, i.e. the editing view.
     *
     * @return the List of all FilteredVideos the Project uses in the first view.
     */
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr getVideoList1() const;

    /**
	* Returns the List of all FilteredVideos the Project uses in the second view, i.e. the analyzing view.
     *
     * @return the List of all FilteredVideos the Project uses in the second view
     */
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr getVideoList2() const;

    /**
     * Returns the player list from the first view (the editing view) of the project.
     *
     * @return the player list from the first view of the project.
     */
	::model::saveable::SaveableList<::model::player::Player>::sptr getPlayerList1() const;

    /**
	* Returns the player from the second view (the analyzing view) of the project.
     *
     * @return the player from the second view of the project.
     */
    ::model::player::Player::sptr getPlayer2() const;

    /**
     * Returns the list of all the FrameDiffs the project uses.
     *
     * @return the list of all the FrameDiffs the project uses.
     */
	::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr getDiffList() const;

    /**
     * Returns the current view of the project.
     *
     * @return the current view of the project.
     */
	::view::ViewState::sptr getView() const;

private:
    ::model::saveable::SaveableList<::model::video::FileVideo>::sptr baseVideoList;
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList1;
	::model::saveable::SaveableList<::model::filter::FilteredVideo>::sptr videoList2;
	::model::saveable::SaveableList<::model::player::Player>::sptr playerList1;
	::model::player::Player::sptr player2;
	::model::saveable::SaveableList<::model::difference::FrameDiff>::sptr diffList;
	::view::ViewState::sptr view;
};

}  // namespace project
}  // namespace controller

#endif  //_PROJECTCONTROLLER_H
