#if !defined(_MEMENTO_H)
#define _MEMENTO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QMap>

namespace model {
namespace project {

class Memento {
public:
	typedef QScopedPointer<Memento> uptr;
	typedef QSharedPointer<Memento> sptr;
	typedef QWeakPointer<Memento> wptr;

	void setBool(bool value, QString name);
	bool getBool(QString name) const;
	void setInt(int value, QString name);
	int getInt(QString name) const;
	void setFloat(float value, QString name);
	float getFloat(QString name) const;
	void setDouble(double value, QString name);
	double getDouble(QString name) const;
	void setString(QString value, QString name);
	QString getString(QString name) const;
	void setPointer(void* pointer, QString name);
	void* getPointer(QString name) const;
	QMap<QString, QString> getVariableMap() const;
	QMap<QString, void*> getPointerMap() const;
private:
	QMap<QString, QString> variableMap;
	QMap<QString, void*> pointerMap;
};

}  // namespace project
}  // namespace model

#endif  //_MEMENTO_H
