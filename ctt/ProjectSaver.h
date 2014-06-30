#if !defined(_PROJECTSAVER_H)
#define _PROJECTSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Saveable.h"

namespace model {
namespace project {

/**
 * A project saver writes a file used to restore the project later. Therefor it takes mementos from every important savable object.
 * Implementations of this interface may have their own conventions which type and structure of files they support.
 */
class ProjectSaver {

public:
	typedef QScopedPointer<ProjectSaver> uptr;
	typedef QSharedPointer<ProjectSaver> sptr;
	typedef QWeakPointer<ProjectSaver> wptr;

	/**
	 * Saves the current state of the project to a file.
	 *
	 * @throws IOException Is thrown if for any reason the file cant be written.
	 */
	void save(QDir path);

private:
	Saveable *toSave;
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTSAVER_H
