#if !defined(_PROJECT_H)
#define _PROJECT_H

#include "SaveableList.h"
#include "Video.h"
#include "FileVideo.h"
#include "FilteredVideo.h"
#include "Player.h"
#include "FrameDiff.h"
#include "ViewState.h"

namespace controller {

/**
 * The project contains all savable objects that already exist in an empty project.
 */
class Project {

public:
	/**
	 * Creates a new project and all savable objects nedded from the start of the program.
	 */
	Project();

	/**
	 * Returns the list of all base videos the project uses, i.e. videos which are directly read from files.
	 *
	 * @return SaveableList<FileVideo> the list of all base videos the project uses.
	 */
	SaveableList<FileVideo> getBaseVideoList();

	/**
	 * Returns the List of all FilteredVideos the Project uses in the first view, i.e. the editing view.
	 *
	 * @return the List of all FilteredVideos the Project uses in the first view.
	 */
	SaveableList<FilteredVideo> getVideoList1();

	/**
	 * Returns the List of all FilteredVideos the Project uses in the second view, i.e. the analysing view.
	 *
	 * @return the List of all FilteredVideos the Project uses in the second view
	 */
	SaveableList<model::video::FilteredVideo> getVideoList2();

	/**
	 * Returns the player list from the first view (the editing view) of the project.
	 *
	 * @return the player list from the first view of the project.
	 */
	SaveableList<model::player::Player> getPlayerList1();

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
	SaveableList<model::difference::FrameDiff> getDiffList();

	/**
	 * Returns the current view of the project.
	 *
	 * @return the current view of the project.
	 */
	view::ViewState getView();

private:
	const SaveableList<model::video::FileVideo> baseVideoList;
	const SaveableList<model::video::FilteredVideo> videoList1;
	const SaveableList<model::video::FilteredVideo> videoList2;
	const SaveableList<model::player::Player> playerList1;
	const model::player::Player player2;
	const SaveableList<model::difference::FrameDiff> diffList;
	const view::ViewState view;
};

}  // namespace controller

#endif  //_PROJECTCONTROLLER_H
