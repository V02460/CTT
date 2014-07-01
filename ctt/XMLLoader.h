#if !defined(_XMLLOADER_H)
#define _XMLLOADER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "ProjectLoader.h"

namespace model {
namespace project {

class XMLLoader : public ProjectLoader {
public:
    typedef QScopedPointer<XMLLoader> uptr;
    typedef QSharedPointer<XMLLoader> sptr;
    typedef QWeakPointer<XMLLoader> wptr;

};

}  // namespace project
}  // namespace model

#endif  //_XMLLOADER_H
