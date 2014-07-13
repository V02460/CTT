#include "ProjectSaver.h"

namespace controller {
namespace project {

using ::controller::project::Project;
using ::exception::NotImplementedException;

void ProjectSaver::save(QDir path, const Project &project) {
	throw new NotImplementedException(QString("ProjectSaver is only an interface and does not implement the save method."));
}

}  // namespace project
}  // namespace controller