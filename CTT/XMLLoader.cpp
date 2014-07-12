#include "XMLLoader.h"

namespace controller {
namespace project {

using ::controller::project::Project;
using ::exception::IOException;
using ::exception::ParseException;
using ::model::saveable::Saveable;

static void restore(QDir path, Project project){
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::ReadOnly)) {
		throw new IOException(QString("File ").append(path.absolutePath()).append(" could not be opened."));
	}
	QDomDocument dom;
	QString *error;
	if (!dom.setContent(&file, error)) {
		file.close();
		throw new ParseException(*error);
	}
	for (QDomNode n = dom.documentElement().firstChild(); !n.isNull(); n = n.nextSibling()) {
		if (!n.isElement) {
			throw new ParseException(QString("Wrong document format. Make sure <elements> only contains <element> tags."));
		}
		QDomElement e = n.toElement();
		// TODO saver if (e.tagName().compare())
	}
}

}  // namespace project
}  // namespace controller