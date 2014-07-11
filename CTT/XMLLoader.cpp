#include "XMLLoader.h"

namespace controller {
namespace project {

using ::controller::project::Project;
using ::exception::IOException;
using ::exception::ParseException;

static void restore(QDir path, Project project){
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		throw new IOException(QString("File could not be opened."));
	}
	QDomDocument dom;
	QString *error;
	if (!dom.setContent(&file, error)) {
		file.close();
		throw new ParseException(*error);
	}
	QDomNodeList elementList = dom.elementsByTagName(QString("element"));
	QList<QDomNodeList> mementos;
	for (int i = 1; i < elementList.length(); i++) {
		QDomNode element = elementList.at(i);
		mementos.append(element.childNodes());
		// TODO continue here
	}
}

}  // namespace project
}  // namespace controller