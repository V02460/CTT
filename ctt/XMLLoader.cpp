#include "XMLLoader.h"

#include "IOException.h"

namespace controller {
namespace project {

using ::exception::IOException;

XMLLoader::XMLLoader() {
}

void XMLLoader::restore(QDir path, Project project) {
	openFile(path);
	createMaps(project);
	restore();
}

void XMLLoader::openFile(QDir path) {
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		throw new IOException(QString("File ").append(path.absolutePath()).append(" could not be opened."));
	}
	xml = new QXmlStreamReader(&file);
	//TODO anfang ignorieren
}

void XMLLoader::createMaps(Project project) {
	/* TODO
	 - map base ids to pointers
	 - create dummies and map their ids to pointers
	 - create mementos and map them to ids
	 */
}

void restore() {
	// TODO actually restore everything
}

}  // namespace project
}  // namespace controller