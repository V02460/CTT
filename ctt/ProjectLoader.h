#if !defined(_PROJECTLOADER_H)
#define _PROJECTLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>
namespace model {
namespace project {

/**
 * A project loader restores a saved project. Therefor it restores every object included in the file through its memento.
 * Implementations of this interface may have their own conventions which type and structure of files they support.
 */
class ProjectLoader {

public:
	typedef QScopedPointer<ProjectLoader> uptr;
	typedef QSharedPointer<ProjectLoader> sptr;
	typedef QWeakPointer<ProjectLoader> wptr;

	/**
	 * The restore method loads a project from the given file. It is highly recommended to override this method.
	 *
	 * @param path The path of the file to load the project from.
	 * @throws NotImplementedException Is thrown by this interface and every implementation, which does not override this method.
	 */
	void restore(QDir path);
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTLOADER_H
