#ifndef _XMLSAVER_H
#define _XMLSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QXmlStreamWriter>

#include "ProjectSaver.h"
#include "Saveable.h"
#include "Memento.h"
#include "ViewState.h"

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

	virtual void save(QString path);

	static const QString SPACE;
	/** String to tell not to change the XML File. */
	static const QString DO_NOT_CHANGE;

	/** Name of the elements tag. */
	static const QString PROJECT;
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
	/** Name of the view tag. */
	static const QString VIEW;
	/** Name of the state attribute. */
	static const QString STATE;


	/** Splitter used for class attributes of SavableList. */
	static const QString SPLITTER;

	/**
	 * Labels for the different base elements to save.
	 *
	 * This enum must be similar in quantity and order to the BASE_ELEMENT_NAMES and
	 * BASE_ELEMENT_CLASS_STRINGS lists and the stringToBaseSaveableType function.
	 */
	enum BaseSaveableType {
		BaseVideoList,
		VideoList1,
		VideoList2,
		PlayerList1,
		Player2,
		DiffList
	};

	/**
	 * A list of base element names.
	 *
	 * This list must be similar in quantity and order to the BaseSaveableType enum.
	 */
	static const QMap<BaseSaveableType, QString> BASE_ELEMENT_NAMES;

	/* TODO properly remove ^ doc
	 * A list of base element class strings.
	 *
	 * This list must be similar in quantity and order to the BaseSaveableType enum.
	 *
	static const QList<QString> BASE_ELEMENT_CLASS_STRINGS;*/

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
	Q_DISABLE_COPY(XMLSaver)

	XMLSaver();

	static XMLSaver::uptr instance;

	QFile *file;
	QXmlStreamWriter *out;
	QList<::model::saveable::Saveable::sptr> pointerList;
	int elementID;

	void initDocument(QString path);
	void mapBasePointer();
	void writeBaseElements();
	void writeMemento(model::saveable::Memento memento);
	void writeElements();
	void writeSingeltons();
	void endDocument();

	static const QMap<BaseSaveableType, QString> initBEN();
};

}  // namespace project
}  // namespace controller

#endif  //_XMLSAVER_H
