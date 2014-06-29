#if !defined(_PROJECTCONTROLLER_H)
#define _PROJECTCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Observer.h"
#include "SaveFileType.h"

namespace controller {

/**
*	The ProjectController manages requests to initialise, save or load a Project.
**/
class ProjectController : public Observer {
public slots:

	/**
	*	Initiates saving an existing Project.
	*	Is called when a notifaction is received that the active Project should be saved.
	**/
	void saveClicked();

	/**
	*	Initiates saving an existing Project with a specified type and to a specified location.
	*	Is called when a notifaction is received that the active Project should be saved.
	*	@param path The path to where the Project should be saved.
	*	@param fileType The type of file as which the Project should be saved.
	**/
	void saveAsClicked(QDir path, SaveFileType fileType);

	/**
	*	Initiates loading an existing Project from a specified location.
	*	Is called when a notifaction is received that a Project should be loaded.
	*	@param path The path from where the Project should be loaded.
	**/
	void loadClicked(QDir path);

	/**
	*	Initiates creating a new Project.
	*	Is called when a notifaction is received that a new Project should be created.
	**/
	void newProject();
private:
	QDir currentSavePath;
	SaveFileType currentSaveFileType;
};

}  // namespace controller

#endif  //_PROJECTCONTROLLER_H
