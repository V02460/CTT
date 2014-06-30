#if !defined(_PROJECTCONTROLLER_H)
#define _PROJECTCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Observer.h"
#include "SaveFileType.h"
#include "ProjectSaver.h"
#include "ProjectLoader.h"

namespace controller {

/**
 *	The ProjectController manages requests to initialise, save or load a Project.
 */
class ProjectController : public Observer {
public:
	typedef QScopedPointer<ProjectController> uptr;
	typedef QSharedPointer<ProjectController> sptr;
	typedef QWeakPointer<ProjectController> wptr;

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

	/**
	 * Sets given saver to be used to save projects.
	 * 
	 * @param saver The saver to be used to save projects.
	 */
	void setSaver(ProjectSaver saver);

	/**
	 * Sets given loader to be used to load projects.
	 *
	 * @param loader The loader to be used to load projects.
	 */
	void setLoader(ProjectLoader loader);
private:
	QDir currentSavePath;
	ProjectSaver saver;
	ProjectLoader loader;
};

}  // namespace controller

#endif  //_PROJECTCONTROLLER_H
