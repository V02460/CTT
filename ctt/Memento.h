#if !defined(_MEMENTO_H)
#define _MEMENTO_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace project {

class Memento {
public:
	typedef QScopedPointer<Memento> uptr;
	typedef QSharedPointer<Memento> sptr;
	typedef QWeakPointer<Memento> wptr;

	void setBool(bool value, QString name);
	bool getBool(QString name);
	void setInt(int value, QString name);
	int getInt(QSting name);
	void setFloat(float value, QString name);
	float getFloat(QString name);
	void setDouble(double value, QString name);
	double getDouble(QString name);
	void setString(QString value, QString name);
	QString getString(QString name);
	void setPointer(Pointer pointer, QString name);
	Pointer getPointer(QString name);
private:
	Map<String, QString> variableMap;
	Map<String, Pointer> pointerMap;
};

}  // namespace project
}  // namespace model

#endif  //_MEMENTO_H
