#include "ProjectLoader.h"

namespace controller {
namespace project {

using ::controller::project::Project;
using ::exception::NotImplementedException;

void ProjectLoader::restore(QDir path, Project project) {
	throw NotImplementedException("The ProjectLoader Interface cannot restore a project.");
}

}  // namespace project
}  // namespace controller