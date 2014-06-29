#if !defined(_PROJECTSAVER_H)
#define _PROJECTSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Saveable.h"

namespace model {
namespace project {

class ProjectSaver {
public:
	void save(QDir path);
private:
	Saveable *toSave;
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTSAVER_H
