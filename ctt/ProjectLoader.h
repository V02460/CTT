#ifndef _PROJECTLOADER_H
#define _PROJECTLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Project.h"

namespace controller {
namespace project {

/**
 * A project loader restores a saved project. Therefor it restores every object included in the file through its
 * memento.
 * Implementations of this interface may have their own conventions which type and structure of files they support.
 */
class ProjectLoader {

public:
    typedef QScopedPointer<ProjectLoader> uptr;
    typedef QSharedPointer<ProjectLoader> sptr;
    typedef QWeakPointer<ProjectLoader> wptr;

    /**
     * Loads a project from the given file. It is highly recommended to override this method.
     *
     * @param path The path of the file to load the project from.
     * @param project The project to load changes to.
     * @throws NotImplementedException Is thrown by this interface and every implementation, which does not override
     *     this method.
     * @throws IOException Is thrown if there is any problem accessing or reading the given file.
     * @throws ParseException Is thrown if the content of the file can not be used to restore a project by the loader.
     */
    static void restore(QDir path, ::controller::project::Project project);
};

}  // namespace project
}  // namespace controller

#endif  //_PROJECTLOADER_H
