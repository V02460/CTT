#include "MainController.h"

#include "NotImplementedException.h"

namespace controller {

using project::SaveFileType;
using project::Project;
using ::exception::NotImplementedException;

Project &MainController::getProject() const {
    throw new NotImplementedException();
}

void MainController::saveClicked() {
    throw new NotImplementedException();
}

void MainController::saveAsClicked(QDir path, SaveFileType fileType) {
    throw new NotImplementedException();
}

void MainController::loadClicked(QDir path) {
    throw new NotImplementedException();
}

void MainController::newProject() {
    throw new NotImplementedException();
}

}  // namespace controller