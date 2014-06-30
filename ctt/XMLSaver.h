#if !defined(_XMLSAVER_H)
#define _XMLSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>
#include "ProjectSaver.h"

namespace model {
namespace project {

class XMLSaver : public ProjectSaver {
public:
	typedef QScopedPointer<XMLSaver> uptr;
	typedef QSharedPointer<XMLSaver> sptr;
	typedef QWeakPointer<XMLSaver> wptr;

};

}  // namespace project
}  // namespace model

#endif  //_XMLSAVER_H
