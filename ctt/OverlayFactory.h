#if !defined(_OVERLAYFACTORY_H)
#define _OVERLAYFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
namespace model {
namespace filter {
namespace overlay {

class OverlayFactory {
public:
	List<QString> getAllOverlayIDs();
	Diff createOverlay(QString id);
private:
	void OverlayFactory();
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_OVERLAYFACTORY_H
