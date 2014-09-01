#ifndef _MAINCONTROLLER_H
#define _MAINCONTROLLER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QObject>

#include "Observer.h"
#include "SaveFileType.h"
#include "Project.h"
#include "XMLLoader.h"
#include "OperationList.h"

namespace controller {

/**
 * The ProjectController manages requests to initialize, save or load a Project.
 */
class MainController : public QObject {
    Q_OBJECT

public:
    typedef QScopedPointer<MainController> uptr;
    typedef QSharedPointer<MainController> sptr;
    typedef QWeakPointer<MainController> wptr;

	MainController();

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
    void saveAsClicked(QString path, project::SaveFileType fileType);

    /**
     * Initiates loading an existing Project from a specified location.
     * Is called when a notification is received that a Project should be loaded.
     *
     * @param path The path from where the Project should be loaded.
     */
    void loadClicked(QString path);

    /**
     * Initiates creating a new Project.
     * Is called when a notification is received that a new Project should be created.
     */
    void newProject();

signals:
	void requestSavePath();
private:
    QString currentSavePath;
    project::SaveFileType currentSaveFileType;
};

}  // namespace controller

#endif  //_MAINCONTROLLER_H
