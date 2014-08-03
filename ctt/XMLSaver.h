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

	/** String to tell not to change the XML File. */
	static const QString DO_NOT_CHANGE;

	/** Name of the elements tag. */
	static const QString ELEMENTS;
	/** Name of the element tag. */
	static const QString ELEMENT;
	/** Name of the variable tag. */
	static const QString VARIABLE;
	/** Name of the pointer tag. */
	static const QString POINTER;
	/** Name of the class attribute. */
	static const QString CLASS;
	/** Name of the id attribute. */
	static const QString ID;
	/** Name of the type attribute. */
	static const QString TYPE;
	/** Name of the name attribute. */
	static const QString NAME;
	/** Name of the value attribute. */
	static const QString VALUE;

	/** Splitter used for class attributes of SavableList. */
	static const QString SPLITTER;

	/* The number of ids must be simular to the number of elements in
	 * the BASE_ELEMENT_NAMES and BASE_ELEMENT_TYPE_STRINGS lists and the id
	 * must represent the position in those lists.
	 */
	/** id given to the base video list. */
	static const int BASE_VIDEO_LIST_ID;
	/** id given to the video list in the 1. view. */
	static const int VIDEO_LIST_1_ID;
	/** id given to the video list in the 2. view. */
	static const int VIDEO_LIST_2_ID;
	/** id given to the player list in the 1. view. */
	static const int PLAYER_LIST_1_ID;
	/** id given to the player in the 2. view. */
	static const int PLAYER_2_ID;
	/** id given to the frame diff list. */
	static const int DIFF_LIST_ID;
	/** id given to the view state. */
	static const int VIEW_ID;

	/**
	 * A list of base element names.
	 *
	 * The order of this list must be determined by the static id's in this class.
	 */
	static const QList<QString> BASE_ELEMENT_NAMES;
	/**
	 * A list of base element type strings.
	 *
	 * The order of this list must be determined by the static id's in this class.
	 */
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
