#include "XMLSaver.h"

#include "IOException.h"

namespace controller {
namespace project {

using ::exception::IOException;
using ::exception::IllegalArgumentException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;
using ::model::saveable::SaveableList;
using ::view::ViewState;

XMLSaver::XMLSaver() {}

const QString XMLSaver::DO_NOT_CHANGE = "Do not edit this file!";

const QString XMLSaver::ELEMENTS = "elements";
const QString XMLSaver::ELEMENT = "element";
const QString XMLSaver::VARIABLE = "variable";
const QString XMLSaver::POINTER = "pointer";
const QString XMLSaver::CLASS = "class";
const QString XMLSaver::ID = "id";
const QString XMLSaver::TYPE = "type";
const QString XMLSaver::TEMPLATE_TYPE = "template";
const QString XMLSaver::NAME = "name";
const QString XMLSaver::VALUE = "value";

const QList<QString> XMLSaver::BASE_ELEMENT_NAMES = QList<QString>()
	<< "baseVideoList"
	<< "videoList1"
	<< "videoList2"
	<< "playerList1"
	<< "player2"
	<< "diffList"
	<< "view";

void XMLSaver::save(QDir path) {
	initDocument(path);
	mapBasePointer();
	writeBaseElements();
	writeElements();
	endDocument();
}

XMLSaver::BaseSaveableType XMLSaver::stringToBaseSaveableType(QString string) {
	for (int i = 0; i < XMLSaver::BASE_ELEMENT_NAMES.length(); i++) {
		if (string == XMLSaver::BASE_ELEMENT_NAMES[i]) {
			return static_cast<BaseSaveableType>(i);
		}
	}
	throw new IllegalArgumentException(string + " is not a base saveable type.");
}

void XMLSaver::initDocument(QDir path) {
	QFile file(path.absolutePath());
	if (!file.open(QIODevice::WriteOnly)) {
		throw new IOException("File " + path.absolutePath() + " could not be opened.");
	}
	out = new QXmlStreamWriter(&file);
	out->setAutoFormatting(true);
	out->writeStartDocument();
	out->writeComment(DO_NOT_CHANGE);
	out->writeStartElement(ELEMENTS);
}

void XMLSaver::mapBasePointer() {
	Project *project = Project::getInstance();
	pointerList.append(project->getBaseVideoList());
	pointerList.append(project->getVideoList1());
	pointerList.append(project->getVideoList2());
	pointerList.append(project->getPlayerList1());
	pointerList.append(project->getPlayer2());
	pointerList.append(project->getDiffList());
}

void XMLSaver::writeBaseElements() {
	int length = pointerList.length();
	for (elementID = 0; elementID < length; elementID++) {
		out->writeStartElement(ELEMENT);
		Saveable::sptr element = pointerList[elementID];
		Saveable::SaveableType type = element->getSaveableType();
		out->writeAttribute(CLASS, Saveable::SAVEABLE_TYPE_STRINGS[type]);
		if (type == Saveable::SaveableType::saveableList) {
			SaveableList<Saveable>::sptr list = element.staticCast<SaveableList<Saveable>>();
			out->writeAttribute(TEMPLATE_TYPE, Saveable::SAVEABLE_TYPE_STRINGS[list->getTemplateType()]);
		}
		out->writeAttribute(ID, QString::number(elementID));
		out->writeAttribute(TYPE, BASE_ELEMENT_NAMES[elementID]);
		writeMemento(element->getMemento());
		out->writeEndElement();
	}
}

void XMLSaver::writeMemento(Memento memento) {
	QMap<QString, QString> variableMap = memento.getVariableMap();
	for (int i = 0; i < variableMap.size(); i++) {
		out->writeEmptyElement(VARIABLE);
		out->writeAttribute(NAME, variableMap.keys()[i]);
		out->writeAttribute(VALUE, variableMap.values()[i]);
	}
	QMap<QString, Saveable::sptr> pointerMap = memento.getPointerMap();
	for (int i = 0; i < pointerMap.size(); i++) {
		out->writeEmptyElement(POINTER);
		out->writeAttribute(NAME, pointerMap.keys()[i]);
		Saveable::sptr pointer = pointerMap.values()[i];
		bool newPointer = true;
		for (int i = 0; i < pointerList.length(); i++) {
			if (pointer == pointerList[i]) { // TODO funktioniert vlt nicht
				out->writeAttribute(ID, QString::number(i));
				newPointer = false;
			}
		}
		if (newPointer) {
			out->writeAttribute(ID, QString::number(pointerList.length()));
			pointerList.append(pointer);
		}
	}
}

void XMLSaver::writeElements() {
	for (; elementID < pointerList.length(); elementID++) {
		out->writeStartElement(ELEMENT);
		Saveable::sptr element = pointerList[elementID];
		Saveable::SaveableType type = element->getSaveableType();
		out->writeAttribute(CLASS, Saveable::SAVEABLE_TYPE_STRINGS[type]);
		if (type = Saveable::SaveableType::saveableList) {
			SaveableList<Saveable>::sptr list = element.staticCast<SaveableList<Saveable>>();
			out->writeAttribute(TEMPLATE_TYPE, Saveable::SAVEABLE_TYPE_STRINGS[list->getTemplateType()]);
		}
		out->writeAttribute(ID, QString::number(elementID));
		writeMemento(element->getMemento());
		out->writeEndElement();
	}
}

void XMLSaver::writeSingeltons() {
	out->writeStartElement(ELEMENT);
	ViewState *view = ViewState::getInstance().data(); // TODO later remove .data();
	out->writeAttribute(CLASS, Saveable::SAVEABLE_TYPE_STRINGS[view->getSaveableType()]);
	out->writeAttribute(ID, QString::number(elementID++)); // TODO ++ should work
	out->writeAttribute(TYPE, BASE_ELEMENT_NAMES[view->getSaveableType()]);
	writeMemento(view->getMemento());
	out->writeEndElement();
}

XMLSaver *XMLSaver::getInstance() {
	if (instance.isNull()) {
		instance.reset(new XMLSaver());
	}
	return instance.data();
}

void XMLSaver::endDocument() {
	out->writeEndDocument();
}

XMLSaver::uptr XMLSaver::instance;

}  // namespace project
}  // namespace controller