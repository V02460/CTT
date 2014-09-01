#include "Memento.h"

namespace model {
namespace saveable {

using ::exception::IllegalArgumentException;
using ::model::saveable::Saveable;

Memento::Memento() {
}

Memento::~Memento() {
}

static const QString TRUE_STRING = "true";
static const QString FALSE_STRING = "false";

void Memento::setBool(QString name, bool value) {
	variableMap.insert(name, value ? TRUE_STRING : FALSE_STRING);
}

bool Memento::getBool(QString name) const {
	if (!variableMap.contains(name)) {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	if (variableMap.value(name) == TRUE_STRING) {
		return true;
	} else if (variableMap.value(name) == FALSE_STRING) {
		return false;
	}
	throw IllegalArgumentException("The variable with name " + name + " in this memento is not a boolean.");
}

void Memento::setInt(QString name, int value) {
	variableMap.insert(name, QString::number(value));
}

int Memento::getInt(QString name) const {
	if (!variableMap.contains(name)) {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	bool valid;
	int value = variableMap.value(name).toInt(&valid);
	if (!valid) {
		throw IllegalArgumentException("The variable with name " + name + " in this memento is not an integer.");
	}
	return value;
}

void Memento::setUInt(QString name, unsigned int value) {
	variableMap.insert(name, QString::number(value));
}

unsigned int Memento::getUInt(QString name) const {
	if (!variableMap.contains(name)) {
		throw IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	bool valid;
	unsigned int value = variableMap.value(name).toUInt(&valid);
	if (!valid) {
		throw IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not an unsigned integer."));
	}
	return value;
}

void Memento::setFloat(QString name, float value) {
	variableMap.insert(name, QString::number(value));
}

float Memento::getFloat(QString name) const {
	if (!variableMap.contains(name)) {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	bool valid;
	float value = variableMap.value(name).toFloat(&valid);
	if (!valid) {
		throw IllegalArgumentException("The variable with name " + name + " in this memento is not a float.");
	}
	return value;
}

void Memento::setDouble(QString name, double value) {
	variableMap.insert(name, QString::number(value));
}

double Memento::getDouble(QString name) const {
	if (!variableMap.contains(name)) {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	bool valid;
	double value = variableMap.value(name).toDouble(&valid);
	if (!valid) {
		throw IllegalArgumentException("The variable with name " + name + " in this memento is not a double.");
	}
	return value;
}

void Memento::setString(QString name, QString value) {
	variableMap.insert(name, value);
}

QString Memento::getString(QString name) const {
	if (!variableMap.contains(name)) {
		throw IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	return variableMap.value(name);
}

void Memento::setSharedPointer(QString name, QSharedPointer<Saveable> pointer) {
	pointerMap.insert(name, pointer);
}

QMap<QString, QString> Memento::getVariableMap() const {
	return variableMap;
}

QMap<QString, Saveable::sptr> Memento::getPointerMap() const {
	return pointerMap;
}

QSharedPointer<Saveable> Memento::getSharedPointer(QString name) const {
	if (!pointerMap.contains(name)) {
		throw IllegalArgumentException("There is no pointer with name " + name + " in this memento.");
	}
	QSharedPointer<Saveable> pointer = pointerMap.value(name);
	return pointer;
}

Saveable* Memento::getPointer(QString name) const {
	return getSharedPointer(name).data();
}

}  // namespace project
}  // namespace model