#if !defined(_PROJECTSAVERFACTORY_H)
#define _PROJECTSAVERFACTORY_H

#include "SaveFileType.h"

namespace model {
namespace project {

class ProjectSaverFactory {
public:
	void save(QDir path, SaveFileType fileType);
};

}  // namespace project
}  // namespace model

#endif  //_PROJECTSAVERFACTORY_H
