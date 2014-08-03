#ifndef _XMLSAVER_H
#define _XMLSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QXmlStreamWriter>

#include "ProjectSaver.h"
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

	static const QString DO_NOT_CHANGE;

	static const QString ELEMENTS;
	static const QString ELEMENT;
	static const QString CLASS;
	static const QString ID;
	static const QString TYPE;
	static const QString VARIABLE;
	static const QString NAME;
	static const QString VALUE;
	static const QString POINTER;

	static const QString LIST;
	static const QString FILE_VIDEO;
	static const QString FILTERED_VIDEO;
	static const QString PLAYER;
	static const QString DIFF;
	static const QString VIEW;

	static const int BASE_VIDEO_LIST_ID;
	static const int VIDEO_LIST_1_ID;
	static const int VIDEO_LIST_2_ID;
	static const int PLAYER_LIST_1_ID;
	static const int PLAYER_2_ID;
	static const int DIFF_LIST_ID;
	static const int VIEW_ID;

	static const QList<QString> BASE_ELEMENT_NAMES;
	static const QList<QString> BASE_ELEMENT_TYPE_STRINGS;

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
