#include "XMLSaver.h"

#include "IOException.h"

namespace controller {
namespace project {

using ::exception::IOException;
using ::model::saveable::Saveable;
using ::model::saveable::Memento;

XMLSaver::XMLSaver() {
}

static const QString DO_NOT_CHANGE = "Do not edit this file!";

static const QString ELEMENTS = "elements";
static const QString ELEMENT = "element";
static const QString CLASS = "class";
static const QString ID = "id";
static const QString TYPE = "type";
static const QString VARIABLE = "variable";
static const QString NAME = "name";
static const QString VALUE = "value";
static const QString POINTER = "pointer";

static const QString LIST = "SavableList";
static const QString FILE_VIDEO = "FileVideo";
static const QString FILTERED_VIDEO = "FilteredVideo";
static const QString PLAYER = "Player";
static const QString DIFF = "FrameDiff";
static const QString VIEW = "View";

static const int BASE_VIDEO_LIST_ID = 0;
static const int VIDEO_LIST_1_ID = 1;
static const int VIDEO_LIST_2_ID = 2;
static const int PLAYER_LIST_1_ID = 3;
static const int PLAYER_2_ID = 4;
static const int DIFF_LIST_ID = 5;
static const int VIEW_ID = 6;

static const QList<QString> BASE_ELEMENT_NAMES = QList<QString>()
	<< "baseVideoList"
	<< "videoList1"
	<< "videoList2"
	<< "playerList1"
	<< "player2"
	<< "diffList"
	<< "view";

static const QList<QString> BASE_ELEMENT_TYPE_STRINGS = QList<QString>()
	<< LIST + ":" + FILE_VIDEO
	<< LIST + ":" + FILTERED_VIDEO
	<< LIST + ":" + FILTERED_VIDEO
	<< LIST + ":" + PLAYER
	<< PLAYER
	<< LIST + ":" + DIFF
	<< VIEW;

void XMLSaver::save(QDir path, const Project &project) {
	initDocument(path);
	mapBasePointer(project);
	writeBaseElements();
	writeElements();
	endDocument();
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

void XMLSaver::mapBasePointer(Project project) {
	pointerList.append(project.getBaseVideoList());
	pointerList.append(project.getVideoList1());
	pointerList.append(project.getVideoList2());
	pointerList.append(project.getPlayerList1());
	pointerList.append(project.getPlayer2());
	pointerList.append(project.getDiffList());
	pointerList.append(project.getView());
}

void XMLSaver::writeBaseElements() {
	int length = pointerList.length();
	for (elementID = 0; elementID < length; elementID++) {
		out->writeStartElement(ELEMENT);
		out->writeAttribute(CLASS, BASE_ELEMENT_TYPE_STRINGS[elementID]);
		out->writeAttribute(ID, QString::number(elementID));
		out->writeAttribute(TYPE, BASE_ELEMENT_NAMES[elementID]);
		writeMemento(pointerList.at(elementID).data()->getMemento());
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
		/* TODO
		 - klasse rausfinden (switch case ?)
		 - attribut class schreiben
		 */
		out->writeAttribute(ID, QString::number(elementID));
		writeMemento(element->getMemento());
		out->writeEndElement();
	}
}

void XMLSaver::endDocument() {
	out->writeEndDocument();
}

}  // namespace project
}  // namespace controller