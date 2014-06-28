


#if !defined(_PROJECTSAVER_H)
#define _PROJECTSAVER_H

#include "Saveable.h"

class ProjectSaver {
public:
	void save(QDir path);
private:
	Saveable *toSave;
};

#endif  //_PROJECTSAVER_H
