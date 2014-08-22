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
	/** Name of the template attribute */
	static const QString TEMPLATE_TYPE;
	/** Name of the name attribute. */
	static const QString NAME;
	/** Name of the value attribute. */
	static const QString VALUE;

	/** Splitter used for class attributes of SavableList. */
	static const QString SPLITTER;

	/**
	 * Labels for the different base elements to save.
	 *
	 * This enum must be similar in quantity and order to the BASE_ELEMENT_NAMES and
	 * BASE_ELEMENT_TYPE_STRINGS lists and the stringToBaseSaveableType function.
	 */
	enum BaseSaveableType {
		BaseVideoList,
		VideoList1,
		VideoList2,
		PlayerList1,
		Player2,
		DiffList,
		View
	};

	/**
	 * A list of base element names.
	 *
	 * This list must be similar in quantity and order to the BaseSaveableType enum.
	 */
	static const QList<QString> BASE_ELEMENT_NAMES;

	/**
	 * A list of base element class strings.
	 *
	 * This list must be similar in quantity and order to the BaseSaveableType enum.
	 */
	static const QList<QString> BASE_ELEMENT_CLASS_STRINGS;

	/**
	 * Returns the BaseSavableType to the given string.
	 *
	 * This function must be similar in quantity and order to the BaseSaveableType enum.
	 *
	 * @param string The string to be made to a BaseSavableType.
	 * @return The BaseSavableType to the given string.
	 */
	static BaseSaveableType stringToBaseSaveableType(QString string);

	/**
	 * Returns the one instance this class can have.
	 */
	static XMLSaver *getInstance();

private:
	XMLSaver();

	static XMLSaver::uptr instance;

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
