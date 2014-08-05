#include "XMLLoader.h"

#include "IOException.h"
#include "ParseException.h"

namespace controller {
namespace project {

using ::exception::IOException;
using ::exception::ParseException;
using ::exception::NotImplementedException;
using ::controller::project::XMLSaver;
using ::controller::project::Project;
using ::model::saveable::Saveable;

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
		throw new IOException("File " + path.absolutePath() + " could not be opened.");
	}
	xml = new QXmlStreamReader(&file);
	if (!xml->readNextStartElement()) { // TODO more to skip?
		throw new ParseException("Document to restore from is empty.");
	}
	if (xml->qualifiedName() != XMLSaver::ELEMENTS) {
		throw new ParseException("Tag <" + XMLSaver::ELEMENTS + "> expected.");
	}
}

void XMLLoader::createMaps(Project project) {
	while (xml->readNextStartElement()) {
		if (xml->qualifiedName() != XMLSaver::ELEMENT) {
			throw new ParseException("Tag <" + XMLSaver::ELEMENT + "> expected.");
		}
		QXmlStreamAttributes attributes = xml->attributes();
		if (!attributes.hasAttribute(XMLSaver::CLASS)) {
			throw new ParseException("Attribute " + XMLSaver::CLASS + " expected.");
		}
		if (!attributes.hasAttribute(XMLSaver::ID)) {
			throw new ParseException("Attribute " + XMLSaver::ID + " expected.");
		}
		QString classString = attributes.value(XMLSaver::CLASS).toString();
		bool valid = false;
		int id = attributes.value(XMLSaver::ID).toInt(&valid);
		if (!valid) {
			throw new ParseException(attributes.value(XMLSaver::ID).toString()
				                     + "is not a valid ID. IDs must be integer.");
		}
		if (attributes.hasAttribute(XMLSaver::TYPE)) {
			XMLSaver::BaseSaveableType type =
				XMLSaver::stringToBaseSaveableType(attributes.value(XMLSaver::TYPE).toString());
			if (classString != XMLSaver::BASE_ELEMENT_CLASS_STRINGS[type]) {
				throw new ParseException("Class of " + XMLSaver::BASE_ELEMENT_NAMES[type] + " must be "
					                     + XMLSaver::BASE_ELEMENT_CLASS_STRINGS[type]);
			}
			switch (type) {
			case XMLSaver::BaseSaveableType::BaseVideoList:
				mapPointer(id, project.getBaseVideoList()); break;
			case XMLSaver::BaseSaveableType::VideoList1:
				mapPointer(id, project.getVideoList1()); break;
			case XMLSaver::BaseSaveableType::VideoList2:
				mapPointer(id, project.getVideoList2()); break;
			case XMLSaver::BaseSaveableType::PlayerList1:
				mapPointer(id, project.getPlayerList1()); break;
			case XMLSaver::BaseSaveableType::Player2:
				mapPointer(id, project.getPlayer2()); break;
			case XMLSaver::BaseSaveableType::DiffList:
				mapPointer(id, project.getDiffList()); break;
			case XMLSaver::BaseSaveableType::View:
				mapPointer(id, project.getView()); break;
			default: throw new NotImplementedException("Unknown base savable type.");
			}
		} else {
			// TODO map Dummy to ID
		}
		// TODO map Memento to ID
	}
}

void XMLLoader::mapPointer(int key, Saveable::sptr value) {
	if (pointerMap.contains(key)) {
		throw new ParseException("Multiple elements with key " + QString::number(key) + " exist.");
	}
	pointerMap.insert(key, value);
}

void XMLLoader::restore() {
	// TODO actually restore everything
}

}  // namespace project
}  // namespace controller


/* TO USE

QXmlStreamReader
	bool					atEnd()
	QXmlStreamAttributes	attributes()
	QString					errorString()
	bool					hasError()
	bool					isComment()
	bool					isEndElement() / isEndDocument()
	bool					isStartElement() / isStartDocument()
	bool					isWhitespace()
	QStringRef				name() / qualifiedName()
	QString					readElementText()
	TokenType / bool		readNext() / readNextStartElement()
	void					skipCurrentElement()

QXmlStreamAttributes
	bool					hasAttribute(QString qualifiedName)
	QStringRef				value(QString qualifiedName)

 */