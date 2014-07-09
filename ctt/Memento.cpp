#include "Memento.h"

namespace model {
namespace saveable {

using ::exception::IllegalArgumentException;

void Memento::setBool(QString name, bool value) {
	variableMap.insert(name, value ? TRUE : FALSE);
}

bool Memento::getBool(QString name) const {
	if (variableMap.contains(name)) {
		if (variableMap.value(name).compare(TRUE)) {
			return true;
		} else if (variableMap.value(name).compare(FALSE)) {
			return false;
		} else {
			throw IllegalArgumentException("The variable with name " + name + " in this memento is not a boolean.");
		}
	} else {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
}

void Memento::setInt(QString name, int value) {
	variableMap.insert(name, QString::number(value));
}

int Memento::getInt(QString name) const {
	if (variableMap.contains(name)) {
		return variableMap.value(name).toInt();
		throw IllegalArgumentException("The variable with name " + name + " in this memento is not an integer.");
	} else {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
}

void Memento::setFloat(QString name, float value) {
	// TODO
}

float Memento::getFloat(QString name) const {
	// TODO
}

void Memento::setDouble(QString name, double value) {
	variableMap.insert(name, QString::number(value));
}

double Memento::getDouble(QString name) const {
	if (variableMap.contains(name)) {
		return variableMap.value(name).toDouble();
		throw IllegalArgumentException("The variable with name " + name + " in this memento is not a double.");
	} else {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
}

void Memento::setString(QString name, QString value) {
	variableMap.insert(name, value);
}

QString Memento::getString(QString name) const {
	if (variableMap.contains(name)) {
		return variableMap.value(name);
	} else {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
}

void Memento::setPointer(QString name, void* pointer) {
	pointerMap.insert(name, pointer);
}

void* Memento::getPointer(QString name) const {
	if (pointerMap.contains(name)) {
		return pointerMap.value(name);
	} else {
		throw IllegalArgumentException("There is no pointer with name " + name + " in this memento.");
	}
}

QMap<QString, QString> Memento::getVariableMap() const {
	return variableMap; // TODO special stuff?
}

QMap<QString, void*> Memento::getPointerMap() const {
	return pointerMap; // TODO special stuff?
}

}  // namespace project
}  // namespace model