


#if !defined(_PROJECTSAVERFACTORY_H)
#define _PROJECTSAVERFACTORY_H

#include "SaveFileType.h"

class ProjectSaverFactory {
public:
	void save(QDir path, SaveFileType fileType);
};

#endif  //_PROJECTSAVERFACTORY_H
