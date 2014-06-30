#if !defined(_OVERLAY_H)
#define _OVERLAY_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "Filter.h"
#include "Frame.h"
#include "Memento.h"

namespace model {
namespace filter {
namespace overlay {

class Overlay : public Filter {
public:
	typedef QScopedPointer<Overlay> uptr;
	typedef QSharedPointer<Overlay> sptr;
	typedef QWeakPointer<Overlay> wptr;
};

}  // namespace overlay
}  // namespace filter
}  // namespace model

#endif  //_OVERLAY_H
