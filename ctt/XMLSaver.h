#if !defined(_XMLSAVER_H)
#define _XMLSAVER_H

#include <QScopedPointer>
#include <QSharedPointer>
#include <QWeakPointer>

#include "ProjectSaver.h"

namespace controller {
namespace project {

/**
 * Saves a project in xml format to a file. The XMLLoader can be used to load the project from this file again.
 */
class XMLSaver : public ProjectSaver {
public:
    typedef QScopedPointer<XMLSaver> uptr;
    typedef QSharedPointer<XMLSaver> sptr;
    typedef QWeakPointer<XMLSaver> wptr;

};

}  // namespace project
}  // namespace controller

#endif  //_XMLSAVER_H
