


#if !defined(_PROJECTCONTROLLER_H)
#define _PROJECTCONTROLLER_H

#include "Observer.h"
#include "SaveFileType.h"

class ProjectController : public Observer {
public:
	slot saveClicked();
	slot saveAsClicked(QDir path, SaveFileType fileType);
	slot loadClicked(QDir path);
	slot newProject();
private:
	QDir currentSavePath;
	SaveFileType currentSaveFileType;
};

#endif  //_PROJECTCONTROLLER_H
