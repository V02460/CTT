#include "Memento.h"

namespace model {
namespace saveable {

using ::exception::IllegalArgumentException;

Memento::Memento() {
}

Memento::~Memento() {
}

void Memento::setBool(QString name, bool value) {
	variableMap.insert(name, value ? TRUE_STRING : FALSE_STRING);
}

bool Memento::getBool(QString name) const {
	if (variableMap.contains(name)) {
		if (variableMap.value(name).compare(TRUE_STRING)) {
			return true;
		} else if (variableMap.value(name).compare(FALSE_STRING)) {
			return false;
		}
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not a boolean."));
	}
	throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
}

void Memento::setInt(QString name, int value) {
	variableMap.insert(name, QString::number(value));
}

int Memento::getInt(QString name) const {
	if (variableMap.contains(name)) {
		bool *valid;
		int value = variableMap.value(name).toInt(valid);
		if (&valid) {
			return value;
		}
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not an integer."));
	}
	throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
}

void Memento::setFloat(QString name, float value) {
	variableMap.insert(name, QString::number(value));
}

float Memento::getFloat(QString name) const {
	if (variableMap.contains(name)) {
		bool valid;
		int value = variableMap.value(name).toFloat(&valid);
		if (valid) {
			return value;
		}
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not a float."));
	}
	throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
}

void Memento::setDouble(QString name, double value) {
	variableMap.insert(name, QString::number(value));
}

double Memento::getDouble(QString name) const {
	if (variableMap.contains(name)) {
		bool valid;
		int value = variableMap.value(name).toDouble(&valid);
		if (valid) {
			return value;
		}
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not a double."));
	}
	throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
}

void Memento::setString(QString name, QString value) {
	variableMap.insert(name, value);
}

QString Memento::getString(QString name) const {
	if (variableMap.contains(name)) {
		return variableMap.value(name);
	}
	throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
}

void Memento::setPointer(QString name, void* pointer) {
	pointerMap.insert(name, pointer);
}

void* Memento::getPointer(QString name) const {
	if (pointerMap.contains(name)) {
		return pointerMap.value(name);
	}
	throw new IllegalArgumentException(QString("There is no pointer with name ").append(name).append(" in this memento."));
}

QMap<QString, QString> Memento::getVariableMap() const {
	return variableMap; // TODO special stuff?
}

QMap<QString, void*> Memento::getPointerMap() const {
	return pointerMap; // TODO special stuff?
}

}  // namespace project
}  // namespace model