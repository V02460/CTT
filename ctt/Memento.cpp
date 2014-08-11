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
		throw new IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	if (variableMap.value(name) == TRUE_STRING) {
		return true;
	} else if (variableMap.value(name) == FALSE_STRING) {
		return false;
	}
	throw new IllegalArgumentException("The variable with name " + name + " in this memento is not a boolean.");
}

void Memento::setInt(QString name, int value) {
	variableMap.insert(name, QString::number(value));
}

int Memento::getInt(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	bool valid;
	int value = variableMap.value(name).toInt(&valid);
	if (!valid) {
		throw new IllegalArgumentException("The variable with name " + name + " in this memento is not an integer.");
	}
	return value;
}

void Memento::setUInt(QString name, unsigned int value) {
	variableMap.insert(name, QString::number(value));
}

unsigned int Memento::getUInt(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException(QString("There is no variable with name ").append(name).append(" in this memento."));
	}
	bool valid;
	unsigned int value = variableMap.value(name).toUInt(&valid);
	if (!valid) {
		throw new IllegalArgumentException(QString("The variable with name ").append(name).append(" in this memento is not an unsigned integer."));
	}
	return value;
}

void Memento::setFloat(QString name, float value) {
	variableMap.insert(name, QString::number(value));
}

float Memento::getFloat(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	bool valid;
	float value = variableMap.value(name).toFloat(&valid);
	if (!valid) {
		throw new IllegalArgumentException("The variable with name " + name + " in this memento is not a float.");
	}
	return value;
}

void Memento::setDouble(QString name, double value) {
	variableMap.insert(name, QString::number(value));
}

double Memento::getDouble(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	bool valid;
	double value = variableMap.value(name).toDouble(&valid);
	if (!valid) {
		throw new IllegalArgumentException("The variable with name " + name + " in this memento is not a double.");
	}
	return value;
}

void Memento::setString(QString name, QString value) {
	variableMap.insert(name, value);
}

QString Memento::getString(QString name) const {
	if (!variableMap.contains(name)) {
		throw new IllegalArgumentException("There is no variable with name " + name + " in this memento.");
	}
	return variableMap.value(name);
}

void Memento::setSharedPointer(QString name, QSharedPointer<Saveable> pointer) {
	pointerMap.insert(name, pointer);
}

template <class T>
T *Memento::getPointer(QString name) const {
	return getSharedPointer<T>(name).data();
}

template <class T>
QSharedPointer<T> Memento::getSharedPointer(QString name) const {
	if (!pointerMap.contains(name)) {
		throw new IllegalArgumentException("There is no pointer with name " + name + " in this memento.");
	}
	QSharedPointer<T> pointer = pointerMap.value(name).dynamicCast();
	if (!pointer) {
		throw new IllegalArgumentException("The pointer is not of requested type.");
	}
	return pointer;
}

QMap<QString, QString> Memento::getVariableMap() const {
	return variableMap;
}

QMap<QString, Saveable::sptr> Memento::getPointerMap() const {
	return pointerMap;
}

// A list of all objects which might be used with the Memento
// This is necessary because *.cpp files are compiled separate, so it's unknown for the compiler for which types to
// generate code.
/* TODO
template class Memento<model::saveable::Saveable>;
template class Memento<model::FilterIntervalList>;
template class Memento<model::difference::FrameDiff>;
template class Memento<model::difference::EarthMoversHistogramDiff>;
template class Memento<model::difference::PixelDiff>;
template class Memento<model::difference::HSLPixelDiff>;
template class Memento<model::difference::YUVPixelDiff>;
template class Memento<model::Module>;
template class Memento<model::filter::Filter>;
template class Memento<model::filter::BlurFilter>;
template class Memento<model::filter::CoffeeFilter>;
template class Memento<model::filter::GreyscaleFilter>;
template class Memento<model::filter::MixFilter>;
template class Memento<model::filter::NoiseFilter>;
template class Memento<model::filter::overlay::Overlay>;
template class Memento<model::filter::overlay::ColoringOverlay>;
template class Memento<model::filter::overlay::HeatmapOverlay>;
template class Memento<model::filter::overlay::MacroblockOverlay>;
template class Memento<model::filter::overlay::MacropartionOverlay>;
template class Memento<model::filter::overlay::MotionVectorOverlay>;
template class Memento<model::filter::RescaleFilter>;
template class Memento<model::filter::RGBChannelFilter>;
template class Memento<model::filter::TimeshiftFilter>;
template class Memento<model::video::Video>;
template class Memento<model::video::FileVideo>;
template class Memento<model::video::FFmpegDataVideo>;
template class Memento<model::video::YUVDataVideo>;
template class Memento<model::filter::FilteredVideo>;
template class Memento<model::player::Player>;
template class Memento<model::UIntegerInterval>;
template class Memento<model::player::VideoScrubber>;
template class Memento<view::ViewState>;
*/

}  // namespace project
}  // namespace model