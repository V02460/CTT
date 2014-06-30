#if !defined(_PROJECTSAVERFACTORY_H)
#define _PROJECTSAVERFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "SaveFileType.h"

namespace model {
namespace project {

class ProjectSaverFactory {
public:
	typedef QScopedPointer<ProjectSaverFactory> uptr;
	typedef QSharedPointer<ProjectSaverFactory> sptr;
	typedef QWeakPointer<ProjectSaverFactory> wptr;

	void save(QDir path, SaveFileType fileType);
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTSAVERFACTORY_H
