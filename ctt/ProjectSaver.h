#ifndef _PROJECTSAVER_H
#define _PROJECTSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "Project.h"

namespace controller {
namespace project {

/**
 * A project saver writes a file used to restore the project later. Therefor it takes mementos from every important
 * savable object.
 * Implementations of this interface may have their own conventions which type and structure of files they support.
 */
class ProjectSaver {

public:
    typedef QScopedPointer<ProjectSaver> uptr;
    typedef QSharedPointer<ProjectSaver> sptr;
    typedef QWeakPointer<ProjectSaver> wptr;

    /**
     * Saves the current state of the project to given file.
     *
     * @param path The path to save to.
     * @param project The project to be saved.
     * @throws IOException Is thrown if for any reason the file cant be written.
     */
    virtual void save(QString path) = 0;
};

}  // namespace project
}  // namespace controller

#endif  //_PROJECTSAVER_H