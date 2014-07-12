#include "Memento.h"

namespace model {
namespace saveable {

using ::exception::IllegalArgumentException;
using ::model::saveable::Saveable;

Memento::Memento() {
}

Memento::~Memento() {
}

void Memento::setBool(QString name, bool value) {
	variableMap.insert(name, value ? TRUE_STRING : FALSE_STRING);
}

bool Memento::getBool(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	if (variableMap.value(name).compare(TRUE_STRING)) {
		return true;
	} else if (variableMap.value(name).compare(FALSE_STRING)) {
		return false;
	}
	throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not a boolean."));
}

void Memento::setInt(QString name, int value) {
	variableMap.insert(name, QString::number(value));
}

int Memento::getInt(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	bool *valid;
	int value = variableMap.value(name).toInt(valid);
	if (!&valid) {
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not an integer."));
	}
	return value;
}

void Memento::setFloat(QString name, float value) {
	variableMap.insert(name, QString::number(value));
}

float Memento::getFloat(QString name) const {
	if (variableMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	bool *valid;
	int value = variableMap.value(name).toFloat(valid);
	if (!&valid) {
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not a float."));
	}
	return value;
}

void Memento::setDouble(QString name, double value) {
	variableMap.insert(name, QString::number(value));
}

double Memento::getDouble(QString name) const {
	if (variableMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	bool *valid;
	int value = variableMap.value(name).toDouble(valid);
	if (!&valid) {
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not a double."));
	}
	return value;
}

void Memento::setString(QString name, QString value) {
	variableMap.insert(name, value);
}

QString Memento::getString(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	return variableMap.value(name);
}

void Memento::setSharedPointer(QString name, QSharedPointer<Saveable> pointer) {
	pointerMap.insert(name, pointer);
}

template <class T> T *Memento::getPointer(QString name) const {
	return getSharedPointer<T>(name).data;
}

template <class T> QSharedPointer<T> Memento::getSharedPointer(QString name) const {
	if (!pointerMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no pointer with name ").append(name).append(" in this memento."));
	}
	QSharedPointer<T> pointer = pointerMap.value(name).dynamicCast();
	if (!pointer) {
		throw new IllegalArgumentException(QString("The pointer is not of requested type."));
	}
	return pointer;
}

QMap<QString, QString> Memento::getVariableMap() const {
	return variableMap;
}

QMap<QString, QSharedPointer<Saveable>> Memento::getPointerMap() const {
	return pointerMap;
}

}  // namespace project
}  // namespace model