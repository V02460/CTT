#if !defined(_PROJECTSAVER_H)
#define _PROJECTSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDir>

#include "Saveable.h"

namespace model {
namespace project {

class ProjectSaver {
public:
	typedef QScopedPointer<ProjectSaver> uptr;
	typedef QSharedPointer<ProjectSaver> sptr;
	typedef QWeakPointer<ProjectSaver> wptr;

	void save(QDir path);
private:
	Saveable *toSave;
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTSAVER_H
