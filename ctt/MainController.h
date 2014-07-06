#if !defined(_MAINCONTROLLER_H)
#define _MAINCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Observer.h"
#include "SaveFileType.h"
#include "Project.h"

namespace controller {

/**
 * The ProjectController manages requests to initialize, save or load a Project.
 */
class MainController : public ::model::Observer {
    Q_OBJECT
public:
    typedef QScopedPointer<MainController> uptr;
    typedef QSharedPointer<MainController> sptr;
    typedef QWeakPointer<MainController> wptr;

    Project &getProject() const;
public slots:

    /**
     * Initiates saving an existing Project.
     * Is called when a notification is received that the active Project should be saved.
     */
    void saveClicked();

    /**
     * Initiates saving an existing Project with a specified type and to a specified location.
     * Is called when a notification is received that the active Project should be saved.
     *
     * @param path The path to where the Project should be saved.
     * @param fileType The type of file as which the Project should be saved.
     */
    void saveAsClicked(QDir path, ::model::project::SaveFileType fileType);

    /**
     * Initiates loading an existing Project from a specified location.
     * Is called when a notification is received that a Project should be loaded.
     *
     * @param path The path from where the Project should be loaded.
     */
    void loadClicked(QDir path);

    /**
     * Initiates creating a new Project.
     * Is called when a notification is received that a new Project should be created.
     */
    void newProject();

private:
    QDir currentSavePath;
    ::model::project::SaveFileType currentSaveFileType;
    Project::uptr project;
};

}  // namespace controller

#endif  //_MAINCONTROLLER_H
