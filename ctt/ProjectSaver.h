


#if !defined(_PROJECTSAVER_H)
#define _PROJECTSAVER_H

#include "Savable.h"

class ProjectSaver {
public:
	void save(QDir path);
private:
	Savable *toSave;
};

#endif  //_PROJECTSAVER_H
