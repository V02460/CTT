#if !defined(_PROJECT_H)
#define _PROJECT_H

#include "SaveableList.h"
#include "Video.h"
#include "Player.h"
#include "FrameDiff.h"
#include "ViewState.h"

namespace controller {

/**
 * The project contains all savable objects that already exist in an empty project.
 */
class Project {

public:
	typedef QScopedPointer<Project> uptr;
	typedef QSharedPointer<Project> sptr;
	typedef QWeakPointer<Project> wptr;

	/**
	 * Creates a new project with given savable objects.
	 *
	 * @param baseVideoList The base video list of the project.
	 * @param videoList1 The video list from the first view of the project.
	 * @param videoList2 The video list from the second view of the project.
	 * @param playerList1 The player list from the first view of the project.
	 * @param player2 The player from the second view of the project.
	 * @param diffList The diff list of the project.
	 * @param view The view of the project.
	 */
    Project(model::SaveableList<model::video::Video>::sptr baseVideoList,
            model::SaveableList<model::video::Video>::sptr videoList1,
            model::SaveableList<model::video::Video>::sptr videoList2,
            model::SaveableList<model::player::Player>::sptr playerList1,
		    model::player::Player::sptr player2,
            model::SaveableList<model::difference::FrameDiff>::sptr diffList,
            view::ViewState view);

	/**
	 * Returns the list of all base videos the project uses, i.e. videos which are directly read from files.
	 *
	 * @return SaveableList<FileVideo> the list of all base videos the project uses.
	 */
    model::SaveableList<model::FileVideo> getBaseVideoList();

	/**
	 * Returns the List of all FilteredVideos the Project uses in the first view, i.e. the editing view.
	 *
	 * @return the List of all FilteredVideos the Project uses in the first view.
	 */
    model::SaveableList<FilteredVideo> getVideoList1();

	/**
	 * Returns the List of all FilteredVideos the Project uses in the second view, i.e. the analysing view.
	 *
	 * @return the List of all FilteredVideos the Project uses in the second view
	 */
    model::SaveableList<model::video::Video> getVideoList2();

	/**
	 * Returns the player list from the first view (the editing view) of the project.
	 *
	 * @return the player list from the first view of the project.
	 */
    model::SaveableList<model::player::Player> getPlayerList1();

	/**
	 * Returns the player from the second view (the analysing view) of the project.
	 *
	 * @return the player from the second view of the project.
	 */
	model::player::Player getPlayer2();

	/**
	 * Returns the list of all the FrameDiffs the project uses.
	 *
	 * @return the list of all the FrameDiffs the project uses.
	 */
    model::SaveableList<model::difference::FrameDiff> getDiffList();

	/**
	 * Returns the current view of the project.
	 *
	 * @return the current view of the project.
	 */
	view::ViewState getView();

private:
    const model::SaveableList<model::video::Video> baseVideoList;
    const model::SaveableList<model::video::Video> videoList1;
    const model::SaveableList<model::video::Video> videoList2;
    const model::SaveableList<model::player::Player> playerList1;
	const model::player::Player player2;
    const model::SaveableList<model::difference::FrameDiff> diffList;
	const view::ViewState view;
};

}  // namespace controller

#endif  //_PROJECTCONTROLLER_H
