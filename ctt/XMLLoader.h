#ifndef _XMLLOADER_H
#define _XMLLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QDomDocument>
#include <QXmlStreamReader>

#include "ProjectLoader.h"
#include "IOException.h"
#include "ParseException.h"
#include "Saveable.h"

namespace controller {
namespace project {

/**
 * Loads a project saved as XML file by the XMLSaver.
 */
class XMLLoader : public ProjectLoader {

public:
    typedef QScopedPointer<XMLLoader> uptr;
    typedef QSharedPointer<XMLLoader> sptr;
    typedef QWeakPointer<XMLLoader> wptr;

	/**
	 * Creates a new XMLLoader.
	 */
	XMLLoader();

	virtual void restore(QDir path, ::controller::project::Project project);

private:
	QXmlStreamReader *xml;

	void openFile(QDir path);
	void createMaps(Project project);
	void restore();
};

}  // namespace project
}  // namespace controller

#endif  //_XMLLOADER_H
