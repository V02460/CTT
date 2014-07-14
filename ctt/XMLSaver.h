#ifndef _XMLSAVER_H
#define _XMLSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QXmlStreamWriter>

#include "ProjectSaver.h"
#include "IOException.h"
#include "Saveable.h"
#include "Memento.h"

namespace controller {
namespace project {

/**
 * Saves a project in XML format to a file. The XMLLoader can be used to load the project from this file again.
 */
class XMLSaver : public ProjectSaver {

public:
    typedef QScopedPointer<XMLSaver> uptr;
    typedef QSharedPointer<XMLSaver> sptr;
    typedef QWeakPointer<XMLSaver> wptr;

	/**
	 * Creates a new XMLSaver.
	 */
	XMLSaver();

	virtual void save(QDir path, const ::controller::project::Project &project);

private:
	QXmlStreamWriter *out;
	QList<::model::saveable::Saveable::sptr> pointerList;
	int elementID;

	void initDocument(QDir path);
	void mapBasePointer(Project project);
	void writeBaseElements();
	void writeMemento(model::saveable::Memento memento);
	void writeElements();
	void endDocument();
};

}  // namespace project
}  // namespace controller

#endif  //_XMLSAVER_H
