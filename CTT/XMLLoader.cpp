#include "XMLLoader.h"

namespace controller {
namespace project {

using ::controller::project::Project;

static void restore(QDir path, Project project){
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		
	}
	QXmlStreamReader reader(&file);
}

}  // namespace project
}  // namespace controller