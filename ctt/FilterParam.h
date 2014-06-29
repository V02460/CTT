#if !defined(_FILTERPARAM_H)
#define _FILTERPARAM_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace filter {

class FilterParam {
public:
	any getValue();
	void FilterParam(QString name);
private:
	QString name;
};

}  // namespace filter
}  // namespace model

#endif  //_FILTERPARAM_H
