#include "MainController.h"

#include "NotImplementedException.h"

namespace controller {

using project::SaveFileType;
using project::Project;
using project::ProjectSaver;
using project::XMLSaver;
using project::XMLLoader;
using operation::OperationList;

MainController::MainController() : currentSavePath(/* TODO standart path here */), currentSaveFileType(SaveFileType::XML) {}

void MainController::saveClicked() {
	if (currentSavePath == "") {
		emit requestSavePath();
	} else {
		saveAsClicked(currentSavePath, currentSaveFileType);
	}
}

void MainController::saveAsClicked(QString path, SaveFileType fileType) {
	currentSavePath = path;

	if (OperationList::getInstance()->hasSaveableChanges()) {
		switch (fileType) {
		case SaveFileType::XML: XMLSaver::getInstance()->save(path); break;
		default: throw IllegalArgumentException("No saver for given file type exists."); break;
		}
	}
}

void MainController::loadClicked(QString path) {
    // TODO check file for type
	XMLLoader::getInstance()->restore(path);
}

void MainController::newProject() {
	Project::getInstance()->clear();
}

}  // namespace controller