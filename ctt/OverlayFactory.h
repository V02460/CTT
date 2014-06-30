#if !defined(_OVERLAYFACTORY_H)
#define _OVERLAYFACTORY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include <QList>

#include "Overlay.h"

namespace model {
namespace filter {
namespace overlay {

class OverlayFactory {
public:
	typedef QScopedPointer<OverlayFactory> uptr;
	typedef QSharedPointer<OverlayFactory> sptr;
	typedef QWeakPointer<OverlayFactory> wptr;

	QList<QString> getAllOverlayIDs();
	Overlay createOverlay(QString id);
private:
	OverlayFactory() {}
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_OVERLAYFACTORY_H
