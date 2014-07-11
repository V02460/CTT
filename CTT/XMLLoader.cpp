#include "XMLLoader.h"

namespace controller {
namespace project {

using ::controller::project::Project;
using ::exception::IOException;

static void restore(QDir path, Project project){
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		throw new IOException(QString("File could not be opened."));
	}
	QXmlStreamReader xml(&file);
	while (!xml.atEnd() && !xml.hasError()) {
		// TODO algorithm
	}
	if (xml.hasError()) {
		// TODO ParseException
	}
}

}  // namespace project
}  // namespace controller